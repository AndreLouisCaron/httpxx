#ifndef _http_MessageBuilder__
#define _http_MessageBuilder__

#include "Message.hpp"
#include "Flags.hpp"

namespace http
{
	class MessageBuilder
	{
	public:
		MessageBuilder();
		MessageBuilder(const Message& message);

		/*!
		 * @brief Obtain the HTTP version used by the remote peer.
		 * @return A numeric error code (should be 1 for now).
		 */
		int major_version() const;

		/*!
		 * @brief Set the HTTP version used by the remote peer.
		 * @param majorVersion The HTTP version
		 */
		void set_major_version(int majorVersion);

		/*!
		 * @brief Obtain the HTTP revision used by the remote peer.
		 * @return A numeric error code (should be 0 or 1 for now).
		 */
		int minor_version() const;

		/*!
		 * @brief Set the HTTP revision used by the remote peer.
		 * @param minorVersion The HTTP revision
		 */
		void set_minor_version(int minorVersion);

		/*!
		 * @brief Obtain parser flags.
		 * @return Flags documenting the parsed request/response object.
		 */
		const Flags& flags() const;

		/*!
		 * @brief Obtain reference to parser flags.
		 * @return Flags documenting the parsed request/response object.
		 */
		Flags& flags();

		/*!
		 * @brief Set parser flags.
		 * @param flags Flags documenting the parsed request/response object.
		 */
		void set_flags(const Flags& flags);

		/*!
		 * @brief Returns a reference to the headers map
		 */
		Message::Headers& headers();

		/*!
		* @brief Returns a reference to the headers map
		*/
		const Message::Headers& headers() const;

		/*!
		 * @brief Returns a string representation of the HTTP version
		 */
		std::string version_to_string() const;

		/*!
		 * @brief Returns the string representation of the message headers
		 */
		std::string headers_to_string() const;

	private:
		int myMajorVersion;
		int myMinorVersion;
		Flags myFlags;
		Message::Headers myHeaders;
	};
}

#endif /* _http_MessageBuilder__ */
