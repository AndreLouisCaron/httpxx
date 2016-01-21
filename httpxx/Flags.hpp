#ifndef _http_Flags_hpp__
#define _http_Flags_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include <httpxx/http-parser/http_parser.h>

namespace http {

        /*!
         * @brief Extra information about the request or response.
         *
         * Flags mainly help with connection/socket management.  In particular,
         * you can determine whether to keep the connection open for keep alive
         * or if you should use switch to an alternate protocol handler
         * (WebSockets, for instance).
         */
    class Flags
    {
        /* nested types. */
    public:
        typedef ::flags Value;

        /* data. */
    private:
        Value myValue;

        /* class methods. */
    public:
		Flags();
		Flags(const Flags& flags);

		void set_chunked(bool chunked);
		void set_keepalive(bool keepalive);
		void set_close(bool close);
		void set_trailing(bool trailing);
		void set_upgrade(bool upgrade);
		void set_skipbody(bool skipbody);

	public:
            /*!
             * @brief Extract the flags set in @a parser.
             */
        static const Flags of ( const ::http_parser& parser );

            /*!
             * @brief Check if the message body is in chuncked format.
             */
        static const Flags chunked ();

            /*!
             * @brief Check if the client requested keep-alive.
             *
             * @note Handling keep alive is only requested by the client, it is
             *  in no fashion required to accept this.  Many servers disable
             *  keep alive for performance reasons when their are hordes of
             *  requests coming mostly from different clients.
             *
             * @see close()
             */
        static const Flags keepalive ();

            /*!
             * @brief Check if a new connection should be established for the
             *  next request.
             *
             * @see keepalive()
             */
        static const Flags close ();

        static const Flags trailing ();

            /*!
             * @brief Check if the client requested a protocol upgrade.
             *
             * Newer HTTP versions support derived protocol (such as WebSockets)
             * to re-use port 80 for additional connections.  When an upgrade is
             * requested, the parser stops accepting data as soon as the headers
             * end.  Whatever data is received next should be interpreted by a
             * specialized protocol handler.
             *
             * In particular, check the "Upgrade" header to determine what
             * protocol was requested.
             */
        static const Flags upgrade ();

        static const Flags skipbody ();

        /* construction. */
    private:
            // Use prototype instances.
        Flags ( Value value );

        /* operators. */
    public:
            /*!
             * @brief Check for signaled flags.
             * @return @c true if all flags in @a rhs are signaled.
             */
        bool operator& ( const Flags& rhs ) const;

		Flags operator| ( const Flags& rhs ) const;

		Flags operator~ () const;
    };

}

#endif /* _http_Flags_hpp__ */
