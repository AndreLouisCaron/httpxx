// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Request.hpp"
#include <string.h>

namespace http {

    int Request::on_url
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Request& request = *static_cast<Request*>(parser->data);
        request.myUrl.append(data, size);
        return (0);
    }

    Request::Request ()
    {
            // initialize parser.
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_REQUEST);
        myParser.data = this;
            // select callbacks.
        mySettings.on_url          = &Request::on_url;
    }

    Request::Request ( Configure configure )
        : Message(configure)
    {
            // initialize parser.
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_REQUEST);
        myParser.data = this;
            // select callbacks.
        mySettings.on_url = &Request::on_url;
    }

    void Request::clear ()
    {
        Message::clear();
            // clear string content, while keeping memory allocated.
        myUrl.clear();
            // (re-)initialize parser.
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_REQUEST);
        myParser.data = this;
    }

    void Request::reset_buffers ()
    {
        std::string empty;
        myUrl.swap(empty), Message::reset_buffers();
    }

    const Method Request::method () const
    {
        return (Method::of(myParser));
    }

    std::string Request::method_name () const
    {
        return (http_method_str(method()));
    }

    bool Request::upgrade () const
    {
        return (myParser.upgrade != 0);
    }

    const std::string& Request::url () const
    {
        return (myUrl);
    }

}
