#include "RequestBuilder.hpp"


namespace http
{
	RequestBuilder::RequestBuilder() : 
		MessageBuilder(), myMethod(Method::get())
	{

	}

	RequestBuilder::RequestBuilder(const Request& request) : 
		MessageBuilder(request), myMethod(Method::get())
	{
		if(request.headers_complete())
		{
			myMethod = request.method();
			myUrl = request.url();
		}
	}

	const Method RequestBuilder::method() const
	{
		return myMethod;
	}

	std::string RequestBuilder::method_name() const
	{
		return myMethod.to_string();
	}

	void RequestBuilder::set_method(const Method& method)
	{
		myMethod = method;
	}

	bool RequestBuilder::upgrade() const
	{
		return flags() & Flags::upgrade();
	}

	void RequestBuilder::set_upgrade(bool upgrade)
	{
		flags().set_upgrade(upgrade);
	}

	const std::string& RequestBuilder::url() const
	{
		return myUrl;
	}

	void RequestBuilder::setUrl(const std::string& url)
	{
		myUrl = url;
	}

	std::string RequestBuilder::request_line() const
	{
		std::string requestLine(method().to_string());
		requestLine += " "; 
		requestLine += url();
		requestLine += " ";
		requestLine += version_to_string();
		requestLine += "\r\n";
		
		return requestLine;
	}

	std::string RequestBuilder::to_string() const
	{
		std::string str(request_line());
		str += headers_to_string();
		str += "\r\n";
		
		return str;
	}
}