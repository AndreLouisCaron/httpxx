#ifndef _http_Method__
#define _http_Method__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <http_parser.h>

namespace http {

        /*!
         * @brief 
         */
    class Method
    {
        /* nested types. */
    private:
        typedef ::http_method Value;

        /* class methods. */
    public:
        static const Method of ( const ::http_parser& parser )
        {
            return (static_cast< ::http_method >(parser.method));
        }

        static const Method del () { return (HTTP_DELETE); }
        static const Method get () { return (HTTP_GET); }
        static const Method head () { return (HTTP_HEAD); }
        static const Method post () { return (HTTP_POST); }
        static const Method put  () { return (HTTP_PUT); }

        static const Method connect () { return (HTTP_CONNECT); }
        static const Method options () { return (HTTP_OPTIONS); }
        static const Method trace () { return (HTTP_TRACE); }

        static const Method copy () { return (HTTP_COPY); }
        static const Method lock () { return (HTTP_LOCK); }
        static const Method mkcol () { return (HTTP_MKCOL); }
        static const Method move () { return (HTTP_MOVE); }
        static const Method propfind () { return (HTTP_PROPFIND); }
        static const Method proppatch () { return (HTTP_PROPPATCH); }
        static const Method unlock () { return (HTTP_UNLOCK); }

        static const Method report () { return (HTTP_REPORT); }
        static const Method mkactivity () { return (HTTP_MKACTIVITY); }
        static const Method checkout () { return (HTTP_CHECKOUT); }
        static const Method merge () { return (HTTP_MERGE); }

        static const Method msearch () { return (HTTP_MSEARCH); }
        static const Method notify () { return (HTTP_NOTIFY); }
        static const Method subscribe () { return (HTTP_SUBSCRIBE); }
        static const Method unsubscribe () { return (HTTP_UNSUBSCRIBE); }

        static const Method patch () { return (HTTP_PATCH); }

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Method ( Value value )
            : myValue(value)
        {}

        /* operators. */
    public:
        bool operator== ( const Method& rhs ) const
        {
            return (myValue == rhs.myValue);
        }

        bool operator!= ( const Method& rhs ) const
        {
            return (myValue != rhs.myValue);
        }
    };

}

#endif /* _http_Method__ */
