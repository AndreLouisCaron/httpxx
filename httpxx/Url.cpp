// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Url.hpp"
#include <iostream>
#include <string.h>

namespace http {

    Url::Url ( const std::string& url, bool isConnect )
    {
        parse(url, isConnect);
    }

    Url::Url ( const char * data, std::size_t size, bool isConnect )
    {
        parse(std::string(data, size), isConnect);
    }

    bool Url::parse( const std::string& url, bool isConnect )
    {
        myData = url;
        memset(&myFields, 0, sizeof(myFields));
        const int result = ::http_parser_parse_url
            (myData.data(), myData.size(), isConnect ? 1 : 0, &myFields);
        myValid = (result == 0);
        return myValid;
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

    std::map<std::string, std::string> Url::query_values() const
    {
        std::map<std::string, std::string> values;
        std::string param = query();
        size_t pos = 0;
        while(param.size() > pos) {
            size_t aidx = param.find('&', pos);
            if(aidx == 0) {
                pos++;
                continue;
            }
            std::string vstr = param.substr(pos, aidx);
            pos += vstr.size() + 1;

            size_t eidx = vstr.find('=', 0);
            if(eidx != std::string::npos && eidx != 0) {
                values[vstr.substr(0, eidx)] = vstr.substr(eidx+1);
            }
        }
        return values;
    }

}
