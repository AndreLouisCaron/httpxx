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

    const char HEADER_TEST[] =
        "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
        "conTENT-Length: 5\r\n"
        "\r\n"
        "HELLO"

        "GET /get_one_header_no_body HTTP/1.0\r\n"
        "\r\n"

        "POST /post_identity_body_world?q=search#hey HTTP/1.0\r\n"
        "Accept: */*\r\n"
        "Transfer-Encoding: identity\r\n"
        "Content-Length: 5\r\n"
        "\r\n"
        "World"
        ;

    int run ( std::istream& stream )
    {
        http::BufferedRequest request;

        int requests = 0;

        const char * data = HEADER_TEST;
        std::size_t size = sizeof(HEADER_TEST)-1;
        std::cerr << "Have " << size << " bytes to feed." << std::endl;
        for (; (size > 0); ++requests)
        {
            // Parse as much data as possible.
            std::cerr << "Feeding..." << std::flush;
            std::size_t used = 0;
            while ((size > 0) && !request.complete())
            {
                std::size_t pass = request.feed(data, size);
                used += pass, data += pass, size -= pass;
            }
            std::cerr << " done! (fed " << used << " bytes)" << std::endl;

            // Check that we've parsed an entire request.
            if (!request.complete())
            {
                std::cerr
                    << "Request still needs data."
                    << std::endl;
                return (EXIT_FAILURE);
            }

            // Prepare to receive another request.
            request.clear();
        }

        // Check the we parsed the exact number of requests.
        if (requests != 3)
        {
            std::cerr
                << "Parsed " << requests << " requests, not 3."
                << std::endl;
            return (EXIT_FAILURE);
        }

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
    std::ifstream file(argv[1]);
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
