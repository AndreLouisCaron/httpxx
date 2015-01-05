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

		const Method method() const;
		std::string method_name() const;
		void set_method(const Method& method);
		
		bool upgrade() const;
		void set_upgrade(bool upgrade);

		const std::string& url() const;
		void setUrl(const std::string& url);

		std::string request_line() const;

		std::string to_string() const;

	private:
		Method myMethod;
		std::string myUrl;
	};
}

#endif /* _http_Request_builder__ */