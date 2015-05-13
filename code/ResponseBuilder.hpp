#ifndef _http_ResponseBuilder__
#define _http_ResponseBuilder__

#include "MessageBuilder.hpp"
#include "Response.hpp"

namespace http
{
	class ResponseBuilder : public MessageBuilder
	{
	public:
		ResponseBuilder();
		ResponseBuilder(const Response& response);

		/*!
		 * @brief Gets the HTTP status code of the response.
		 */
		int status() const;

		/*!
		 * @brief Gets the reason string of the HTTP status code.
		 */
		std::string status_reason() const;

		/*!
		 * @brief Sets the HTTP status code.
		 * @param status The HTTP status code.
		 */
		void set_status(int status);

		/*!
		 * Gets a string representation of the HTTP response status line.
		 */
		std::string status_line() const;

		/*
		 * Gets a full string representation of the HTTP response.
		 */
		std::string to_string() const;
		
	private:
		int myStatus;
	};
}

#endif /* _http_ResponseBuilder__ */