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

    int run ( std::istream& stream )
    {
        // Parse HTTP response.
        http::BufferedResponse response;
        char data[1024];
        do {
            stream.read(data, sizeof(data));
            std::size_t size = stream.gcount();
            std::size_t used = 0;
            std::size_t pass = 0;
            while ((used < size) && !response.complete()) {
                used += response.feed(data+used, size-used);
            }
        }
        while ((stream.gcount() > 0) && !response.complete());

        // Check that we've parsed an entire response.
        if (!response.complete())
        {
            std::cerr
                << "Response still needs data."
                << std::endl;
            return (EXIT_FAILURE);
        }

        // Extract header.
        std::cout
            << response.body()
            << std::endl;
        return (EXIT_SUCCESS);
    }

}

int main ( int argc, char ** argv )
try
{
    if (argc > 2)
    {
        std::cerr
            << "Trailing arguments ignored."
            << std::endl;
    }
    if (argc == 1) {
        return ::run(std::cin);
    }
    std::ifstream file(argv[1], std::ios::binary);
    if (!file.is_open())
    {
        std::cerr
            << "Could not open input file."
            << std::endl;
        return (EXIT_FAILURE);
    }
    return ::run(file);
}
catch ( const std::exception& error )
{
    std::cerr
        << error.what()
        << std::endl;
    return (EXIT_FAILURE);
}
