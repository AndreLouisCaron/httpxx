#ifndef _http_Request__
#define _http_Request__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <http_parser.h>

#include "Message.hpp"
#include "Method.hpp"

namespace http {

        /*!
         * @brief Parser for HTTP request.
         */
    class Request :
         public Message
    {
        /* class methods. */
    private:
        static int on_url
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_path
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_query_string
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_fragment
            ( ::http_parser * parser, const char * data, size_t size );

        /* data. */
    private:
        std::string myUrl;
        std::string myPath;
        std::string myQuery;
        std::string myFragment;

        /* construction. */
    public:
            /*!
             * @brief Build a fresh, independant HTTP parser.
             */
        Request ();

        /* methods. */
    public:
            /*!
             * @brief Empty all request content, but keep allocated buffers.
             */
        void clear ();

        const Method method () const;

            /*!
             * @brief Check if the client requested a connection upgrade.
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        bool upgrade () const;

            /*!
             * @brief Get the request URL.
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        const std::string& url () const;

            /*!
             * @brief Get the request path (subset of the URL).
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        const std::string& path () const;

            /*!
             * @brief Get the request fragment (subset of the URL).
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        const std::string& fragment () const;
    };

}

#endif /* _http_Request__ */
