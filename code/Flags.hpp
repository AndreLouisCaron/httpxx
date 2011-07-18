#ifndef _http_Flags_hpp__
#define _http_Flags_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "http_parser.h"

namespace http {

    class Flags
    {
        /* nested types. */
    public:
        typedef ::flags Value;

        /* data. */
    private:
        Value myValue;

        /* class methods. */
    public:
        static const Flags of ( const ::http_parser& parser )
        {
            return (static_cast< ::flags >(parser.flags));
        }

        static const Flags chunked ()
        {
            return (F_CHUNKED);
        }

        static const Flags keepalive ()
        {
            return (F_CONNECTION_KEEP_ALIVE);
        }

        static const Flags close ()
        {
            return (F_CONNECTION_CLOSE);
        }

        static const Flags trailing ()
        {
            return (F_TRAILING);
        }

        static const Flags upgrade ()
        {
            return (F_UPGRADE);
        }

        static const Flags skipbody ()
        {
            return (F_SKIPBODY);
        }

        /* construction. */
    private:
        Flags ( Value value )
            : myValue(value)
        {}

        /* operators. */
    public:
        bool operator& ( const Flags& rhs ) const
        {
            return ((myValue & rhs.myValue) != 0);
        }
    };

}

#endif /* _http_Flags_hpp__ */
