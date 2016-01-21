#ifndef _http_Url__
#define _http_Url__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <httpxx/http-parser/http_parser.h>

#include <string>

namespace http {

    class Url
    {
        /* data. */
    private:
        std::string myData;
        ::http_parser_url myFields;

        /* construction. */
    public:
        Url ( const std::string& url, bool isConnect = false );
        Url ( const char * data, std::size_t size, bool isConnect = false );

        /* methods. */
    public:
        bool has_schema () const;
        std::string schema () const;

        bool has_host () const;
        std::string host () const;

        bool has_port () const;
        std::string port () const;

        bool has_path () const;
        std::string path () const;

        bool has_query () const;
        std::string query () const;

        bool has_fragment () const;
        std::string fragment () const;

		std::string absolute_path() const;
		std::string path_and_query() const;

    private:
        bool has_field ( http_parser_url_fields field ) const;
        std::string get_field ( http_parser_url_fields field ) const;
    };

}

#endif /* _http_Url__ */
