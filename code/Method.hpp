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
        static const Method of ( const ::http_parser& parser );

        static const Method del ();
        static const Method get ();
        static const Method head ();
        static const Method post ();
        static const Method put  ();

        static const Method connect ();
        static const Method options ();
        static const Method trace ();

        static const Method copy ();
        static const Method lock ();
        static const Method mkcol ();
        static const Method move ();
        static const Method propfind ();
        static const Method proppatch ();
        static const Method unlock ();

        static const Method report ();
        static const Method mkactivity ();
        static const Method checkout ();
        static const Method merge ();

        static const Method msearch ();
        static const Method notify ();
        static const Method subscribe ();
        static const Method unsubscribe ();

        static const Method patch ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Method ( Value value );

        /* operators. */
    public:
        bool operator== ( const Method& rhs ) const;
        bool operator!= ( const Method& rhs ) const;
    };

}

#endif /* _http_Method__ */
