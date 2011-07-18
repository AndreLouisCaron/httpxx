#ifndef _http_Response__
#define _http_Response__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "http_parser.h"
#include "Message.hpp"

namespace http {

    class Response :
        public Message
    {
        /* construction. */
    public:
            /*!
             * @brief Build a fresh, independant HTTP parser.
             */
        Response ();

        /* methods. */
    public:
        int status () const;
    };

}

#endif /* _http_Response__ */
