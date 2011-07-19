// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Flags.hpp"

namespace http {

    const Flags Flags::of ( const ::http_parser& parser )
    {
        return (static_cast< ::flags >(parser.flags));
    }

    const Flags Flags::chunked ()
    {
        return (F_CHUNKED);
    }

    const Flags Flags::keepalive ()
    {
        return (F_CONNECTION_KEEP_ALIVE);
    }

    const Flags Flags::close ()
    {
        return (F_CONNECTION_CLOSE);
    }

    const Flags Flags::trailing ()
    {
        return (F_TRAILING);
    }

    const Flags Flags::upgrade ()
    {
        return (F_UPGRADE);
    }

    const Flags Flags::skipbody ()
    {
        return (F_SKIPBODY);
    }

    Flags::Flags ( Value value )
        : myValue(value)
    {
    }

    bool Flags::operator& ( const Flags& rhs ) const
    {
        return ((myValue & rhs.myValue) != 0);
    }

}
