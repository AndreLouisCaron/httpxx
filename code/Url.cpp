// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Url.hpp"
#include <iostream>

namespace http {

    Url::Url ( const std::string& url, bool isConnect )
        : myData(url)
    {
        const int result = ::http_parser_parse_url
            (myData.data(), myData.size(), isConnect ? 1 : 0, &myFields);
        if (result != 0)
        { 
           // TODO: handle failure.
        }
    }

    Url::Url ( const char * data, std::size_t size, bool isConnect )
        : myData(data, size)
    {
        const int result = ::http_parser_parse_url
            (myData.data(), myData.size(), isConnect ? 1 : 0, &myFields);
        if (result != 0)
        {
            // TODO: handle failure.
        }
    }

    bool Url::has_schema () const
    {
        return (has_field(UF_SCHEMA));
    }

    std::string Url::schema () const
    {
        return (get_field(UF_SCHEMA));
    }

    bool Url::has_host () const
    {
        return (has_field(UF_HOST));
    }

    std::string Url::host () const
    {
        return (get_field(UF_HOST));
    }

    bool Url::has_port () const
    {
        return (has_field(UF_PORT));
    }

    std::string Url::port () const
    {
        return (get_field(UF_PORT));
    }

    bool Url::has_path () const
    {
        return (has_field(UF_PATH));
    }

    std::string Url::path () const
    {
        return (get_field(UF_PATH));
    }

    bool Url::has_query () const
    {
        return (has_field(UF_QUERY));
    }

    std::string Url::query () const
    {
        return (get_field(UF_QUERY));
    }

    bool Url::has_fragment () const
    {
        return (has_field(UF_FRAGMENT));
    }

    std::string Url::fragment () const
    {
        return (get_field(UF_FRAGMENT));
    }

    bool Url::has_field ( http_parser_url_fields field ) const
    {
        return ((myFields.field_set & (1 << int(field))) != 0);
    }

    std::string Url::get_field ( http_parser_url_fields field ) const
    {
        if (!has_field(field)) {
            return ("");
        }
        return (myData.substr(myFields.field_data[int(field)].off,
                              myFields.field_data[int(field)].len));
    }

	std::string Url::absolute_path() const
	{
		std::string absolutePath;
		if(has_path())
		{
			absolutePath += path();
		}

		if(absolutePath.empty())
		{
			absolutePath = "/";
		}
		
		return absolutePath;
	}

	std::string Url::path_and_query() const
	{
		std::string pathAndQuery(absolute_path());

		if(has_query())
		{
			pathAndQuery += "?";
			pathAndQuery += query();
		}

		return pathAndQuery;
	}

}
