// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Error.hpp"
#include "Flags.hpp"
#include "Method.hpp"
#include "Message.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <iostream>
#include <ctime>

namespace {

        // Random number in [0, 1].
    double random () {
        return (double(std::rand()) / double(RAND_MAX));
    }

        // Random number in [lower, upper].
    std::size_t random ( std::size_t lower, std::size_t upper )
    {
        const double alpha = random();
        const double blend = double(lower) + alpha*(double(upper-lower));
        return (std::size_t(blend + 0.5));
    }

        // Feed [data, data+size) to parser in random increments.
    void feed ( http::Message& message, const char * data, std::size_t size )
    {
        for ( std::size_t i = 0; (i < size-1); ) {
            i += message.feed(data+i, random(1, size-i));
        }
    }

        // Example request.
    const char REQUEST[] =
        "GET /demo HTTP/1.1\r\n"
        "Content-Type: text/xml\r\n"
        "Content-Length: 16\r\n"
        "\r\n"
        "<xml>hello</xml>"
        ;

}

int main ( int, char ** )
try
{
        // Parse request in random increments.
    http::Request request;
    feed(request, REQUEST, sizeof(REQUEST));
    if ( !request.complete() ) {
        std::cerr << "Request still needs data." << std::endl;
        return (EXIT_FAILURE);
    }
        // Show that we've parsed it correctly.
    std::cout
        << "Connection: '" << request.header("Connection") << "'."
        << std::endl;
    std::cout
        << "Host: '" << request.header("Host") << "'."
        << std::endl;
    std::cout
        << "Fubar: '" << request.header("Fubar") << "'."
        << std::endl;
    std::cout
        << "Body: '" << request.body() << "'."
        << std::endl;
}
catch ( const std::exception& error )
{
    std::cerr
        << error.what()
        << std::endl;
    return (EXIT_FAILURE);
}
