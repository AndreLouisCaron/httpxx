// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Error.hpp"

namespace {

#define HTTP_ERRNO_GEN(n, s) s,
    const char* STRINGS[] = {
        HTTP_ERRNO_MAP(HTTP_ERRNO_GEN)
    };
#undef HTTP_ERRNO_GEN

}

namespace http {

    Error::Error ( ::http_errno number )
        : myNumber(number)
    {
    }

    const char * Error::what () const throw()
    {
        return (STRINGS[myNumber]);
    }

}
