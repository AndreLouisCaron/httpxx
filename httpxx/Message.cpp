// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Message.hpp"
#include "Error.hpp"
#include "Flags.hpp"
#include "icompare.hpp"

#include <algorithm>
#include <cstring>
#include <utility>

#include <iostream>

namespace {

    struct Clear {
        typedef std::pair<const std::string, std::string> Header;
        void operator() ( Header& header ) const { header.second.clear(); }
    };

    class Matches
    {
        const std::string& myField;
    public:
        Matches ( const std::string& field )
            : myField(field)
        {}
        bool operator() ( const std::pair<std::string,std::string>& field )
        {
            return (http::ieq(field.first, myField));
        }
    };

}

namespace http {

    int Message::on_message_begin ( ::http_parser * parser )
    {
        Message& message = *static_cast<Message*>(parser->data);
        message.myComplete = false;
        message.myHeadersComplete = false;
        return (0);
    }

    int Message::on_message_complete ( ::http_parser * parser )
    {
        Message& message = *static_cast<Message*>(parser->data);
        message.myComplete = true;
        if ( !message.myCurrentValue.empty() )
        {
            message.myHeaders[message.myCurrentField] =
                message.myCurrentValue;
            message.myCurrentField.clear();
            message.myCurrentValue.clear();
        }

        // Force the parser to stop after the request is parsed so clients
        // can process the request (or response).  This is to properly
        // handle HTTP/1.1 pipelined requests.
        http_parser_pause(parser, 1);

        return (0);
    }

    int Message::on_header_field
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Message& message = *static_cast<Message*>(parser->data);
        if ( !message.myCurrentValue.empty() )
        {
            message.myHeaders[message.myCurrentField] =
                message.myCurrentValue;
            message.myCurrentField.clear();
            message.myCurrentValue.clear();
        }
        message.myCurrentField.append(data, size);
        return (0);
    }

    int Message::on_header_value
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Message& message = *static_cast<Message*>(parser->data);
        message.myCurrentValue.append(data, size);
        return (0);
    }

    int Message::on_headers_complete ( ::http_parser * parser )
    {
        Message& message = *static_cast<Message*>(parser->data);
        if ( !message.myCurrentValue.empty() )
        {
            message.myHeaders[message.myCurrentField] =
                message.myCurrentValue;
            message.myCurrentField.clear();
            message.myCurrentValue.clear();
        }
        message.myHeadersComplete = true;

        // Force the parser to stop after the headers are parsed so clients
        // can process the request (or response).  This is to properly
        // handle HTTP/1.1 pipelined requests.
        http_parser_pause(parser, 1);

        return (0);
    }

    Message::Message ( Configure configure )
    {
            // make sure message is not seen as complete.
        myComplete = false;
        myHeadersComplete = false;
            // select callbacks.
        ::memset(&mySettings, 0, sizeof(mySettings));
        mySettings.on_message_complete = &Message::on_message_complete;
        mySettings.on_message_begin    = &Message::on_message_begin;
        mySettings.on_header_field     = &Message::on_header_field;
        mySettings.on_header_value     = &Message::on_header_value;
        mySettings.on_headers_complete = &Message::on_headers_complete;

            // Apply extra configuration.
        if (configure) {
            configure(mySettings);
        }
    }

    Message::~Message ()
    {
    }

    void Message::clear ()
    {
            // make sure message is not seen as complete.
        myComplete = false;
        myHeadersComplete = false;
            // clear string content, while keeping memory allocated.
        std::for_each(myHeaders.begin(), myHeaders.end(), Clear());
    }

    void Message::reset_buffers ()
    {
        std::map<std::string,std::string> empty;
        myHeaders.swap(empty);
    }

    std::size_t Message::feed ( const void * data, ::size_t size )
    {
        return (feed(static_cast<const char*>(data), size));
    }

    std::size_t Message::feed ( const char * data, ::size_t size )
    {
        std::size_t used = ::http_parser_execute
            (&myParser, &mySettings, data, size);

        const ::http_errno error =
            static_cast< ::http_errno >(myParser.http_errno);

        // The 'on_message_complete' and 'on_headers_complete' callbacks fail
        // on purpose to force the parser to stop between pipelined requests.
        // This allows the clients to reliably detect the end of headers and
        // the end of the message.  Make sure the parser is always unpaused
        // for the next call to 'feed'.
        if (error == HPE_PAUSED) {
            ::http_parser_pause(&myParser, 0);
        }

        if (used < size)
        {
            if (error == HPE_PAUSED)
            {
                // Make sure the byte that triggered the pause
                // after the headers is properly processed.
                if (!myComplete)
                {
                    used += ::http_parser_execute
                        (&myParser, &mySettings, data+used, 1);
                }
            }
            else {
                throw (Error(error));
            }
        }

        return (used);
    }

    bool Message::complete () const
    {
        return (myComplete);
    }

    bool Message::headers_complete () const
    {
        return (myHeadersComplete);
    }

    int Message::major_version () const
    {
        return (myParser.http_major);
    }

    int Message::minor_version () const
    {
        return (myParser.http_minor);
    }

    const Flags Message::flags () const
    {
        return (Flags::of(myParser));
    }

    bool Message::has_header ( const std::string& field ) const
    {
        const Headers::const_iterator match =
            std::find_if(myHeaders.begin(), myHeaders.end(), ::Matches(field));
        return ((match != myHeaders.end()) && !match->second.empty());
    }

    std::string Message::header ( const std::string& field ) const
    {
        const Headers::const_iterator match =
            std::find_if(myHeaders.begin(), myHeaders.end(), ::Matches(field));
        if ( match == myHeaders.end() ) {
            return ("");
        }
        return (match->second);
    }

	const Message::Headers& Message::headers() const
	{
		return myHeaders;
	}

    bool Message::should_keep_alive () const
    {
        return (::http_should_keep_alive
                (const_cast< ::http_parser* >(&myParser)) != 0);
    }

}
