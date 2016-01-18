// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <httpxx/http.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace {

    int run ( std::istream& stream, const std::string& field )
    {
        // Parse HTTP request.
        http::Request request;
        char data[1024];
        std::size_t head = 0;
        std::size_t body = 0;
        do {
            stream.read(data, sizeof(data));
            std::size_t size = stream.gcount();
            std::size_t used = 0;
            while ((used < size) && !request.headers_complete())
            {
                const std::size_t pass = request.feed(data+used, size-used);
                used += pass, head += pass;
                if (request.headers_complete())
                {
                    std::cerr
                        << "Head size: " << head << "."
                        << std::endl;
                }
            }
            while ((used < size) && !request.complete())
            {
                const std::size_t pass = request.feed(data+used, size-used);
                used += pass, body += pass;
                if (request.complete())
                {
                    std::cerr
                        << "Body size: " << body << "."
                        << std::endl;
                }
            }
            head += used;
        }
        while ((stream.gcount() > 0) && !request.complete());

        // Check that we've parsed an entire request.
        if ( !request.complete() ) {
            std::cerr << "Request still needs data." << std::endl;
            return (EXIT_FAILURE);
        }

        // Extract header.
        std::cout
            << request.header(field)
            << std::endl;
        return (EXIT_SUCCESS);
    }

}

int main ( int argc, char ** argv )
try
{
    if (argc < 2)
    {
        std::cerr
            << "Which header?"
            << std::endl;
        return (EXIT_FAILURE);
    }
    if (argc > 3)
    {
        std::cerr
            << "Trailing arguments ignored."
            << std::endl;
    }
    const std::string field(argv[1]);
    if (argc == 2) {
        return ::run(std::cin, field);
    }
    std::ifstream file(argv[2], std::ios::binary);
    if (!file.is_open())
    {
        std::cerr
            << "Could not open input file."
            << std::endl;
        return (EXIT_FAILURE);
    }
    return ::run(file, field);

}
catch ( const std::exception& error )
{
    std::cerr
        << error.what()
        << std::endl;
    return (EXIT_FAILURE);
}
