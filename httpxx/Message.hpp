#ifndef _http_Message__
#define _http_Message__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <httpxx/http-parser/http_parser.h>

#include <map>
#include <string>

namespace http {

    class Flags;

        /*!
         * @brief Common denominator of @c Request and @c Response classes.
         *
         * This classes is an implementation detail and should not be
         * instantiated directly.  You should use its services through instances
         * of the the @c Request and @c Response classes instead.
         */
    class Message
    {
        /* nested types. */
	public:
        typedef std::map<std::string, std::string> Headers;

    protected:
        typedef void(*Configure)(::http_parser_settings&);

        /* class methods. */
    private:
        static int on_message_begin ( ::http_parser * parser );

        static int on_message_complete ( ::http_parser * parser );

        static int on_header_field
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_header_value
            ( ::http_parser * parser, const char * data, size_t size );

        static int on_headers_complete ( ::http_parser * parser );

        /* data. */
    protected:
        ::http_parser_settings mySettings;
        ::http_parser myParser;

            // Accumulate info, then push to map.
        std::string myCurrentField;
        std::string myCurrentValue;
        std::map<std::string, std::string> myHeaders;

            // Signal when message is complete.
        bool myComplete;
        bool myHeadersComplete;

        /* construction. */
    protected:
            /*!
             * @brief Build a fresh, independant HTTP parser.
             * @param configure Extra parser configuration by base classes.
             */
        Message ( Configure configure=0 );

    private:
           // Not copyable.
        Message ( const Message& );

    public:
        virtual ~Message ();

        /* methods. */
    public:
            /*!
             * @brief Empty all request content, but keep allocated buffers.
             */
        virtual void clear ();

            /*!
             * @brief Release memory owned by all internal buffers.
             */
        virtual void reset_buffers ();

            /*!
             * @brief Feed data to the parser.
             * @param data Address of first byte to read.
             * @param size Number of bytes to read, starting at @a data.
             * @return Number of bytes processed.
             * @throws Error An error occured while reading the HTTP request.
             *
             * The parser pauses after the headers are finished and after the
             * body is finished, causing this method to return even if all
             * @a size bytes have not been consumed.  The parser is implicitly
             * unpaused so if you want to buffer an entire request, you can
             * use a loop like:
             *
             * @code
             *  // process HTTP headers until available data
             *  // is exhausted or the HTTP body finishes.
             *  while ((size > 0) && !request.complete())
             *  {
             *    // process as moch content as possible.
             *    const std::size_t pass =
             *      request.feed(data, size);
             *
             *    // update data pointers.
             *    data += pass, size -= pass;
             *  }
             *  if (request.complete())
             *  {
             *    // process buffered request.
             *  }
             * @endcode
             *
             * or you can process only headers using a loop like:
             * @code
             *  // process HTTP headers until available data
             *  // is exhausted or the HTTP headers finish.
             *  while ((size > 0) && !request.headers_complete())
             *  {
             *    // process as moch content as possible.
             *    const std::size_t pass =
             *      request.feed(data, size);
             *
             *    // update data pointers.
             *    data += pass, size -= pass;
             *  }
             *  if (request.headers_complete())
             *  {
             *    // check host header, content-length, etc.
             *  }
             * @endcode
             *
             * @see complete()
             * @see headers_complete()
             */
        std::size_t feed ( const void * data, ::size_t size );

            /*!
             * @brief Feed data to the parser.
             * @param data Address of first byte to read.
             * @param size Number of bytes to read, starting at @a data.
             * @return Number of bytes processed.
             *
             * @see complete()
             */
        std::size_t feed ( const char * data, ::size_t size );

           /*!
            * @brief Check if the request has been completely parsed.
            */
        bool complete () const;

           /*!
            * @brief Check if the request headers have been completely parsed.
            */
        bool headers_complete () const;

            /*!
             * @brief Obtain the HTTP version used by the remote peer.
             * @return A numeric error code (should be 1 for now).
             */
        int major_version () const;

            /*!
             * @brief Obtain the HTTP revision used by the remote peer.
             * @return A numeric error code (should be 0 or 1 for now).
             */
        int minor_version () const;

            /*!
             * @brief Obtain parser flags.
             * @return Flags documenting the parsed request/response object.
             */
        const Flags flags () const;

            /*!
             * @brief Check if the request included a header named @a field.
             * @param field Name of header to check.
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        bool has_header ( const std::string& field ) const;

            /*!
             * @brief Obtain the value of the header named @a field.
             * @param field Name of header to check.
             * @return An empty string if the header was not present, the header
             *  value otherwise.
             *
             * @warning This value is unspecified until @c headerscomplete()
             *  returns @c true.
             */
        std::string header ( const std::string& field ) const;

		/*!
		 * @brief Returns a const reference to the headers map
		 * @warning This value is unspecified until @c headerscomplete()
		 * returns @c true.
		 */
		const Headers& headers() const;

        /*!
         * @brief Check if this is not the last request/response.
         * @return @c false if you should shut down the connection, @c true if
         *  you should leave it open.
         *
         * For the party sending the response, this indicates if you should
         * send the "Connection: close" header.  For the party receiving the
         * response, this indicates if you should close the connection after
         * reading the message.
         */
        bool should_keep_alive () const;

        /* operators. */
    private:
           // Not copyable.
        Message& operator= ( const Message& );
    };

}

#endif /* _http_Message__ */
