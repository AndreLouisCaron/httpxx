#ifndef _http_BufferedMessage_hpp__
#define _http_BufferedMessage_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011-2012
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <string>
#include "Request.hpp"
#include "Response.hpp"

namespace http {

    /*!
     * @brief Default strategy for handling message bodies: buffer them.
     * @tparam Message base class, must be @c Request or @c Response.
     */
    template<class Base>
    class BufferedMessage :
        public Base
    {
        /* data. */
    private:
        std::string myBody;

        /* methods. */
    public:
        /*!
         * @brief Obtain the buffered message body.
         */
        const std::string& body () const
        {
            return (myBody);
        }

        /*!
         * @brief Clear the body contents after processing them.
         *
         * This method can be used between calls to @c feed() once @c
         * headers_complete() returns @c true, allowing you to process the
         * body in chunks at your convenience.
         */
        void clear_body ()
        {
            myBody.clear();
        }

        /*!
         * @brief Empty all message content, but keep allocated buffers.
         */
        virtual void clear ()
        {
            myBody.clear(), Base::clear();
        }

        /*!
         * @brief Release memory owned by all internal buffers.
         */
        virtual void reset_buffers ()
        {
            myBody.swap(std::string()), Base::reset_buffers();
        }

    protected:
        virtual void accept_body ( const char * data, std::size_t size )
        {
            myBody.append(data, size);
        }
    };

    typedef BufferedMessage<Request> BufferedRequest;
    typedef BufferedMessage<Response> BufferedResponse;

}

#endif /* _http_BufferedMessage_hpp__ */
