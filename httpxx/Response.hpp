#ifndef _http_Response__
#define _http_Response__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Message.hpp"

namespace http {

        /*!
         * @brief Parser for HTTP responses.
         *
         * @c Response objects are typically used on the "client" side of the
         * HTTP connection.  After you've sent an HTTP request to the server,
         * feed incoming data to an object of this class.
         *
         * @note This class is a response @e parser.  It cannot be used to
         *  format outgoing responses.
         *
         * For high performance applications, you'll probably need to watch out
         * for memory usage.  Response objects may be used to parse additional
         * HTTP responses by using the @c clear() method.  This ensures that
         * allocate buffers are re-used instead of dumped.  Reusing response
         * objects will likely leed to faster parsing and reduced memory
         * fragmentation in long running processes.
         *
         * @code
         *  http::Response response;
         *  // parse response.
         *  while (!response.complete()) {
         *    const int transferred = ::recv(socket, data, size, 0);
         *    if (transferred == 0) {
         *      break;
         *    }
         *    response.feed(data, transferred);
         *  }
         *  if (!response.complete()) {
         *    // ...
         *  }
         *  // process response.
         *  const std::string& contenttype = request.header("Content-Type");
         *  if (contenttype == "text/html") {
         *    // ...
         *  }
         *  // signal end of transfer.
         *  if (!(response.flags()&Flags::keepalive())) {
         *    ::shutdown(socket, SD_BOTH);
         *  }
         *  // prepare to process another response.
         *  response.clear();
         * @endcode
         */
    class Response :
        public Message
    {
        /* construction. */
    public:
            /*!
             * @brief Build a fresh, independant HTTP response parser.
             */
        Response ();

    protected:
        Response ( Configure configure );

        /* methods. */
    public:
        virtual void clear ();

            /*!
             * @brief Obtain the HTTP status code returned by the server.
             * @return Numeric HTTP status code.
             *
             * @note 200 is not the only valid response code.  Make sure to read
             *  the HTTP specification to learn how to interpret this value
             *  correctly.
             */
        int status () const;
    };

}

#endif /* _http_Response__ */
