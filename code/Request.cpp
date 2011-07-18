// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Request.hpp"

namespace http {

    int Request::on_url
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Request& request = *static_cast<Request*>(parser->data);
        request.myUrl.append(data, size);
        return (0);
    }

    int Request::on_path
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Request& request = *static_cast<Request*>(parser->data);
        request.myPath.append(data, size);
        return (0);
    }

    int Request::on_query_string
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Request& request = *static_cast<Request*>(parser->data);
        request.myQuery.append(data, size);
        return (0);
    }

    int Request::on_fragment
        ( ::http_parser * parser, const char * data, size_t size )
    {
        Request& request = *static_cast<Request*>(parser->data);
        request.myFragment.append(data, size);
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
        mySettings.on_path         = &Request::on_path;
        mySettings.on_fragment     = &Request::on_fragment;
        mySettings.on_query_string = &Request::on_query_string;
    }

    void Request::clear ()
    {
        Message::clear();
            // clear string content, while keeping memory allocated.
        myUrl.clear();
        myPath.clear();
        myQuery.clear();
        myFragment.clear();
            // (re-)initialize parser.
        ::memset(&myParser, 0, sizeof(myParser));
        ::http_parser_init(&myParser, HTTP_REQUEST);
        myParser.data = this;
    }

    const Method Request::method () const
    {
        return (Method::of(myParser));
    }

    bool Request::upgrade () const
    {
        return (myParser.upgrade != 0);
    }

    const std::string& Request::url () const
    {
        return (myUrl);
    }

    const std::string& Request::path () const
    {
        return (myPath);
    }

    const std::string& Request::fragment () const
    {
        return (myFragment);
    }

}
