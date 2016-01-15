// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Method.hpp"

namespace http {

    const Method Method::of ( const ::http_parser& parser )
    {
        return (static_cast< ::http_method >(parser.method));
    }

    const Method Method::del ()
    {
        return (HTTP_DELETE);
    }

    const Method Method::get ()
    {
        return (HTTP_GET);
    }

    const Method Method::head ()
    {
        return (HTTP_HEAD);
    }

    const Method Method::post ()
    {
        return (HTTP_POST);
    }

    const Method Method::put  ()
    {
        return (HTTP_PUT);
    }

    const Method Method::connect ()
    {
        return (HTTP_CONNECT);
    }

    const Method Method::options ()
    {
        return (HTTP_OPTIONS);
    }

    const Method Method::trace ()
    {
        return (HTTP_TRACE);
    }

    const Method Method::copy ()
    {
        return (HTTP_COPY);
    }

    const Method Method::lock ()
    {
        return (HTTP_LOCK);
    }

    const Method Method::mkcol ()
    {
        return (HTTP_MKCOL);
    }

    const Method Method::move ()
    {
        return (HTTP_MOVE);
    }

    const Method Method::propfind ()
    {
        return (HTTP_PROPFIND);
    }

    const Method Method::proppatch ()
    {
        return (HTTP_PROPPATCH);
    }

    const Method Method::unlock ()
    {
        return (HTTP_UNLOCK);
    }

    const Method Method::report ()
    {
        return (HTTP_REPORT);
    }

    const Method Method::mkactivity ()
    {
        return (HTTP_MKACTIVITY);
    }

    const Method Method::checkout ()
    {
        return (HTTP_CHECKOUT);
    }

    const Method Method::merge ()
    {
        return (HTTP_MERGE);
    }

    const Method Method::msearch ()
    {
        return (HTTP_MSEARCH);
    }

    const Method Method::notify ()
    {
        return (HTTP_NOTIFY);
    }

    const Method Method::subscribe ()
    {
        return (HTTP_SUBSCRIBE);
    }

    const Method Method::unsubscribe ()
    {
        return (HTTP_UNSUBSCRIBE);
    }

    const Method Method::patch ()
    {
        return (HTTP_PATCH);
    }

    Method::Method ( Value value )
        : myValue(value)
    {
    }

    bool Method::operator== ( const Method& rhs ) const
    {
        return (myValue == rhs.myValue);
    }

    bool Method::operator!= ( const Method& rhs ) const
    {
        return (myValue != rhs.myValue);
    }

    Method::operator Value () const
    {
        return (myValue);
    }

	std::string Method::to_string() const
	{
		return http_method_str(myValue);
	}

}
