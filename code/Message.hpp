#ifndef _http_Message__
#define _http_Message__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "http_parser.h"

#include <map>
#include <string>

namespace http {

    class Flags;

        /*!
         * @brief Common denominator of @c Request and @c Response classes.
         */
    class Message
    {
        /* nested types. */
    private:
        typedef std::map<std::string, std::string> Headers;

        /* class methods. */
    private:
        static int on_message_begin ( ::http_parser * parser );

        static int on_message_complete ( ::http_parser * parser );

        static int on_header_field
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_header_value
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_headers_complete ( ::http_parser * parser );

        static int on_body
            ( ::http_parser * parser, const char * data, size_t size );

        /* data. */
    protected:
        ::http_parser_settings mySettings;
        ::http_parser myParser;

            // Accumulate info, then push to map.
        std::string myCurrentField;
        std::string myCurrentValue;
        std::map<std::string, std::string> myHeaders;

            // Accumulate whole body.
        std::string myBody;

            // Signal when message is complete.
        bool myComplete;
        bool myHeadersComplete;

        /* construction. */
    protected:
            /*!
             * @brief Build a fresh, independant HTTP parser.
             */
        Message ();

    private:
           // Not copyable.
        Message ( const Message& );

        /* methods. */
    public:
            /*!
             * @brief Empty all request content, but keep allocated buffers.
             */
        void clear ();

            /*!
             * @brief Feed data to the parser.
             * @param data Address of first byte to read.
             * @param size Number of bytes to read, starting at @a data.
             * @return Number of bytes processed.
             *
             * @see complete()
             */
        std::size_t feed ( const void * data, ::size_t size );

            /*!
             * @brief Feed data to the parser.
             * @param data Address of first byte to read.
             * @param size Number of bytes to read, starting at @a data.
             * @return Number of bytes processed.
             *
             * @see complete()
             */
        std::size_t feed ( const char * data, ::size_t size );

           /*!
            * @brief Check if the request has been completely parsed.
            */
        bool complete () const;

           /*!
            * @brief Check if the request headers have been completely parsed.
            */
        bool headerscomplete () const;

        int majorversion () const;

        int minorversion () const;

        const Flags flags () const;

            /*!
             * @brief Check if the request included a header named @a field.
             * @param field Name of header to check.
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        bool hasheader ( const std::string& field ) const;

            /*!
             * @brief Obtain the value of the header named @a field.
             * @param field Name of header to check.
             * @return An empty string if the header was not present, the header
             *  value otherwise.
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        std::string header ( const std::string& field ) const;

            /*!
             * @brief Obtain the entire request body.
             *
             * @warning This value is undefined until @c complete() returns
             *  @c true.
             */
        const std::string& body () const;

        /* operators. */
    private:
           // Not copyable.
        Message& operator= ( const Message& );
    };

}

#endif /* _http_Message__ */
