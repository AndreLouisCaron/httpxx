#ifndef _http_UserBufferedMessage_hpp__
#define _http_UserBufferedMessage_hpp__

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
     * @brief Using user specified storage for body to avoid memory copy.
     * @tparam Base Message base class, must be @c Request or @c Response.
     * @tparam T Type of storage which supports append(const char*, size_t).
     */
    template<class Base,class T>
    class UserBufferedMessage
    : public Base
    {
        /* nested types. */
    private:
      typedef UserBufferedMessage<Base, T> Self;

        /* class methods. */
    private:
        static int on_body
            ( ::http_parser * parser, const char * data, size_t size )
        {
            static_cast<Self*>(parser->data)->myBody.append(data, size);
            return (0);
        }

        static void extra_configuration ( ::http_parser_settings& settings )
        {
            settings.on_body = &Self::on_body;
        }

        /* construction. */
    public:
        UserBufferedMessage (T &userbuff)
	  : Base(&Self::extra_configuration), myBody(userbuff)
        {
        }

        /* data. */
    private:
        T &myBody;
    };

    template<class T>
    class UserBufferedRequest : public UserBufferedMessage<Request, T>
    {
    public:
      UserBufferedRequest(T &userbuf)
        : UserBufferedMessage<Request, T>(userbuf)
      {
      }
    private:
      UserBufferedRequest() {}
    };

    template<class T>
    class UserBufferedResponse : public UserBufferedMessage<Response, T>
    {
    public:
      UserBufferedResponse(T &userbuf)
        : UserBufferedMessage<Response, T>(userbuf)
      {
      }
    private:
      UserBufferedResponse() {}
    };
}

#endif /* _http_UserBufferedMessage_hpp__ */
