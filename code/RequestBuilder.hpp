#ifndef _http_Request_builder__
#define _http_Request_builder__

#include "MessageBuilder.hpp"
#include "Request.hpp"

namespace http
{
	class RequestBuilder : public MessageBuilder
	{
	public:
		RequestBuilder();
		RequestBuilder(const Request& request);

		/*!
		 * @brief Obtain the HTTP method used by the client for the request.
		 * @return One of the enumeration values.
		 */
		const Method method() const;

		/*!
		 * @brief Get the HTTP method as a string.
		 */
		std::string method_name() const;

		/*!
		 * @brief Set the HTTP method used by the client for the request.
		 * @param method The HTTP method.
		 */
		void set_method(const Method& method);
		
		/*!
		 * @brief Check if client requested a connection upgrade.
		 */
		bool upgrade() const;

		/*!
		 * @brief Sets if client requested a connection upgrade.
		 * @param upgrade The value of the upgrade flag.
		 */
		void set_upgrade(bool upgrade);

		/*!
		 * @brief Get the request URL.
		 */
		const std::string& url() const;

		/*!
		 * @brief Sets the request URL.
		 * @param url The request URL.
		 */
		void setUrl(const std::string& url);

		/*!
		 * @brief Gets a string representation of the request line.
		 */
		std::string request_line() const;

		/*!
		 * @brief Gets a full string representation of the request.
		 */
		std::string to_string() const;

	private:
		Method myMethod;
		std::string myUrl;
	};
}

#endif /* _http_Request_builder__ */