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

		int status() const;
		std::string status_reason() const;
		void set_status(int status);

		std::string status_line() const;
		std::string to_string() const;
		
	private:
		int myStatus;
	};
}

#endif /* _http_ResponseBuilder__ */