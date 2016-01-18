#ifndef _http_Method__
#define _http_Method__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <httpxx/http-parser/http_parser.h>

#include <string>

namespace http {

        /*!
         * @brief Enumeration of "well known" HTTP request methods.
         */
    class Method
    {
        /* nested types. */
    private:
        typedef ::http_method Value;

        /* class methods. */
    public:
            /*!
             * @brief Extract the method set in @a parser.
             */
        static const Method of ( const ::http_parser& parser );

        //! @defgroup Standard HTTP methods.
        //! @{

            /*!
             * @brief Delete the resource.
             */
        static const Method del ();

            /*!
             * @brief Fetch the resource.
             */
        static const Method get ();

            /*!
             * @brief Like GET, but don't send a response body (headers only).
             */
        static const Method head ();

            /*!
             * @brief Submit information about the resource.
             *
             * @see put()
             * @see patch()
             */
        static const Method post ();

            /*!
             * @brief Replace the resource.
             *
             * @see post()
             * @see patch()
             */
        static const Method put  ();

        //! @}

        //! @defgroup Standard HTTP extension methods.
        //! @{

            /*!
             * @brief Partially update the resource (RFC 5789).
             *
             * @see post()
             * @see put()
             */
        static const Method patch ();

        //! @}

            /*!
             * @brief Establish a connection for tunnelling another protocol.
             */
        static const Method connect ();

            /*!
             * @brief Fetch requirements or capabilities w/ respect to the URI.
             */
        static const Method options ();

            /*!
             * @brief Echo request as response body.
             *
             * The TRACE method is used for network diagnostics (e.g. to detect
             * proxies and gateways) and for testing, to check what is received
             * at the other end of the connection.
             */
        static const Method trace ();

        //! @defgroup WebDAV HTTP extension methods.
        //! @{

        static const Method copy ();
        static const Method lock ();
        static const Method mkcol ();
        static const Method move ();
        static const Method propfind ();
        static const Method proppatch ();
        static const Method unlock ();

        //! @}

        //! @defgroup Subversion HTTP extension methods.
        //! @{

        static const Method report ();
        static const Method mkactivity ();
        static const Method checkout ();
        static const Method merge ();

        //! @}

        //! @defgroup Universal Plug and Play (UPNP) HTTP extension methods.
        //! @{

        static const Method msearch ();
        static const Method notify ();
        static const Method subscribe ();
        static const Method unsubscribe ();

		std::string to_string() const;

        //! @}

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Method ( Value value );

        /* operators. */
    public:
        bool operator== ( const Method& rhs ) const;
        bool operator!= ( const Method& rhs ) const;

        operator Value () const;
    };

}

#endif /* _http_Method__ */
