#ifndef _http_Error__
#define _http_Error__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <httpxx/http-parser/http_parser.h>

#include <exception>

namespace http {

        /*!
         * @brief Raised when a parser signals inability to parse fed data.
         */
    class Error :
        public std::exception
    {
        /* data. */
    private:
        ::http_errno myNumber;

        /* construction. */
    public:
            /*!
             * @brief Build an @c Error instance documenting a specific error.
             * @param number Numeric error code.
             */
        explicit Error ( ::http_errno number );

        /* methods. */
    public:
            /*!
             * @brief Obtain a textual description of the error.
             * @return A pointer to the start of a statically allocated error
             *  message.  Do @e not delete the returned error message.
             */
        virtual const char * what () const throw();
    };

}

#endif /* _http_Error__ */
