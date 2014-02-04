#ifndef _http_BufferedMessage_hpp__
#define _http_BufferedMessage_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011-2012
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <string>
#include "Request.hpp"
#include "Response.hpp"

namespace http {

    /*!
     * @brief Default strategy for handling message bodies: buffer them.
     * @tparam Message base class, must be @c Request or @c Response.
     */
    template<class Base>
    class BufferedMessage :
        public Base
    {
        /* nested types. */
    private:
        typedef BufferedMessage<Base> Self;

        /* class methods. */
    private:
        static int on_body
            ( ::http_parser * parser, const char * data, size_t size )
        {
            static_cast<Self*>(parser->data)->myBody.append(data, size);
            return (0);
        }

        static void extra_configuration ( ::http_parser_settings& settings )
        {
            settings.on_body = &Self::on_body;
        }

        /* construction. */
    public:
        BufferedMessage ()
            : Base(&Self::extra_configuration)
        {
        }

        /* data. */
    private:
        std::string myBody;

        /* methods. */
    public:
        /*!
         * @brief Obtain the buffered message body.
         */
        const std::string& body () const
        {
            return (myBody);
        }

        /*!
         * @brief Clear the body contents after processing them.
         *
         * This method can be used between calls to @c feed() once @c
         * headers_complete() returns @c true, allowing you to process the
         * body in chunks at your convenience.
         */
        void clear_body ()
        {
            myBody.clear();
        }

        /*!
         * @brief Empty all message content, but keep allocated buffers.
         */
        virtual void clear ()
        {
            myBody.clear(), Base::clear();
        }

        /*!
         * @brief Release memory owned by all internal buffers.
         */
        virtual void reset_buffers ()
        {
            std::string().swap(myBody), Base::reset_buffers();
        }
    };

    typedef BufferedMessage<Request> BufferedRequest;
    typedef BufferedMessage<Response> BufferedResponse;

}

#endif /* _http_BufferedMessage_hpp__ */
