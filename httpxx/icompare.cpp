// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011-2012
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file iequal.cpp
 * @brief Case-insensitive string comparisons.
 */

#include "icompare.hpp"
#include <string.h>

namespace http {

    int icmp ( const std::string& lhs, const std::string& rhs )
    {
#ifdef _MSC_VER
        return (::_stricmp(lhs.c_str(), rhs.c_str()));
#else
        return (::strcasecmp(lhs.c_str(), rhs.c_str()));
#endif
    }

    bool ieq ( const std::string& lhs, const std::string& rhs )
    {
        return (icmp(lhs, rhs) == 0);
    }

    bool ilt ( const std::string& lhs, const std::string& rhs )
    {
        return (icmp(lhs, rhs) < 0);
    }

    bool ile ( const std::string& lhs, const std::string& rhs )
    {
        return (icmp(lhs, rhs) <= 0);
    }

    bool igt ( const std::string& lhs, const std::string& rhs )
    { 
        return (icmp(lhs, rhs) > 0);
    }

    bool ige ( const std::string& lhs, const std::string& rhs )
    {
        return (icmp(lhs, rhs) >= 0);
    }

}
