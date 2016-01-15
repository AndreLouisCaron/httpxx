// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Response.hpp"
#include <string.h>

namespace http {

    Response::Response ()
    {
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_RESPONSE);
        myParser.data = this;
    }

    Response::Response ( Configure configure )
        : Message(configure)
    {
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_RESPONSE);
        myParser.data = this;
    }

    void Response::clear ()
    {
        Message::clear();
            // (re-)initialize parser.
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_RESPONSE);
        myParser.data = this;
    }

    int Response::status () const
    {
        return (myParser.status_code);
    }

}
