#ifndef _http_Request__
#define _http_Request__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Message.hpp"
#include "Method.hpp"

namespace http {

        /*!
         * @brief Parser for HTTP requests.
         *
         * @c Request objects are typically used on the "server" side of the
         * HTTP connection.  After you've accepted a connection from a client,
         * feed incoming data to an object of this class.
         *
         * @note This class is a request @e parser.  It cannot be used to format
         *  outgoing requests.
         *
         * For high performance applications, you'll probably need to watch out
         * for memory usage.  Request objects may be used to parse additional
         * HTTP requests by using the @c clear() method.  This ensures that
         * allocate buffers are re-used instead of dumped.  Reusing request
         * objects will likely leed to faster parsing and reduced memory
         * fragmentation in long running processes.
         *
         * @code
         *  http::Request request;
         *  // parse request.
         *  while (!request.complete()) {
         *    const int transferred = ::recv(socket, data, size, 0);
         *    if (transferred == 0) {
         *      break;
         *    }
         *    request.feed(data, transferred);
         *  }
         *  if (!request.complete()) {
         *    // ...
         *  }
         *  // process request.
         *  const std::string& host = request.header("Host");
         *  if (host == "www.example.com") {
         *    // ...
         *  }
         *  // signal end of transfer.
         *  if (!(request.flags()&Flags::keepalive())) {
         *    ::shutdown(socket, SD_BOTH);
         *  }
         *  // prepare to process another request.
         *  request.clear();
         * @endcode
         */
    class Request :
         public Message
    {
        /* class methods. */
    private:
        static int on_url
            ( ::http_parser * parser, const char * data, size_t size );

        /* data. */
    private:
        std::string myUrl;

        /* construction. */
    public:
            /*!
             * @brief Build a fresh, independant HTTP request parser.
             */
        Request ();

    protected:
        Request ( Configure configure );

        /* methods. */
    public:
            /*!
             * @brief Empty all request content, but keep allocated buffers.
             */
        virtual void clear ();

            /*!
             * @brief Release memory owned by all internal buffers.
             */
        virtual void reset_buffers ();

            /*!
             * @brief Obtain the HTTP method used by the client for the request.
             * @return One of a few enumeration values.
             *
             * @note There are a variety of methods other than GET and POST.
             *  Make sure to validate that this corresponds to one of the HTTP
             *  methods you plan to support.
             */
        const Method method () const;

            /*!
             * @brief Get the HTTP method as a string.
             */
        std::string method_name () const;

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
    };

}

#endif /* _http_Request__ */
