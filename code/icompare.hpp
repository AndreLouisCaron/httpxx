#ifndef _http_iequal_hpp__
#define _http_iequal_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011-2012
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file iequal.hpp
 * @brief Case-insensitive string comparisons.
 */

#include <string>

namespace http {

    int icmp ( const std::string& lhs, const std::string& rhs );
    bool ieq ( const std::string& lhs, const std::string& rhs );
    bool ilt ( const std::string& lhs, const std::string& rhs );
    bool ile ( const std::string& lhs, const std::string& rhs );
    bool igt ( const std::string& lhs, const std::string& rhs );
    bool ige ( const std::string& lhs, const std::string& rhs );

}

#endif /* _http_iequal_hpp__ */
