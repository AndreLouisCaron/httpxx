#include "MessageBuilder.hpp"

#include <stdio.h>

#if defined(_MSC_VER) && !defined(snprinf)
#define snprintf sprintf_s
#endif

namespace http
{
	MessageBuilder::MessageBuilder() :
		myMajorVersion(1), myMinorVersion(0)
	{

	}

	MessageBuilder::MessageBuilder(const Message& message) : 
		myMajorVersion(1), myMinorVersion(0)
	{
		if(message.headers_complete())
		{
			myMajorVersion = message.major_version();
			myMinorVersion = message.minor_version();
			myFlags = message.flags();
			myHeaders = message.headers();
		}
	}

	int MessageBuilder::major_version() const
	{
		return myMajorVersion;
	}

	void MessageBuilder::set_major_version(int majorVersion)
	{
		myMajorVersion = majorVersion;
	}

	int MessageBuilder::minor_version() const
	{
		return myMinorVersion;
	}

	void MessageBuilder::set_minor_version(int minorVersion)
	{
		myMinorVersion = minorVersion;
	}

	const Flags& MessageBuilder::flags() const
	{
		return myFlags;
	}

	Flags& MessageBuilder::flags()
	{
		return myFlags;
	}

	void MessageBuilder::set_flags(const Flags& flags)
	{
		myFlags = flags;
	}

	Message::Headers& MessageBuilder::headers()
	{
		return myHeaders;
	}

	const Message::Headers& MessageBuilder::headers() const
	{
		return myHeaders;
	}

	std::string MessageBuilder::version_to_string() const
	{
		std::string versionString("HTTP/");
		char majorVersion[16] = {0};
		char minorVersion[16] = {0};

		snprintf(majorVersion, 16, "%d", major_version());
		snprintf(minorVersion, 16, "%d", minor_version());

		versionString += majorVersion;
		versionString += ".";
		versionString += minorVersion;

		return versionString;
	}

	std::string MessageBuilder::headers_to_string() const
	{
		std::string headersString;
		for(Message::Headers::const_iterator cit = myHeaders.begin(); cit != myHeaders.end(); ++cit)
		{
			headersString += cit->first;
			headersString += ": ";
			headersString += cit->second;
			headersString += "\r\n";
		}

		return headersString;
	}
}
