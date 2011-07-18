#ifndef _http_Error__
#define _http_Error__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "http_parser.h"
#include <exception>

namespace http {

        /*!
         */
    class Error :
        public std::exception
    {
        /* data. */
    private:
        ::http_errno myNumber;

        /* construction. */
    public:
        explicit Error ( ::http_errno number );

        /* methods. */
    public:
        virtual const char * what () const;
    };

}

#endif /* _http_Error__ */
