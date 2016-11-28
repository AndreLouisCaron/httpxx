if GCC
AM_CXXFLAGS = -Wall -Wextra -Wpointer-arith -Werror -fPIC
AM_CFLAGS =   -Wall -Wextra -Wpointer-arith -Werror -fPIC
AM_LDFLAGS =
endif GCC

if XLC
AM_CXXFLAGS = -brtl -qarch=com -qlibansi -qthreaded
AM_CFLAGS =   -brtl -qarch=com -qlibansi -qthreaded
AM_LDFLAGS = -brtl -expall
endif XLC

lib_LIBRARIES = libhttpxx.a
libhttpxx_a_SOURCES = Error.cpp Flags.cpp icompare.cpp Message.cpp MessageBuilder.cpp Method.cpp Request.cpp RequestBuilder.cpp Response.cpp ResponseBuilder.cpp Url.cpp http-parser/http_parser.c
pkginclude_HEADERS = Error.hpp Flags.hpp icompare.hpp Message.hpp MessageBuilder.hpp Method.hpp Request.hpp RequestBuilder.hpp Response.hpp ResponseBuilder.hpp Url.hpp UserBufferedMessage.hpp BufferedMessage.hpp http.hpp
httpparserdir=$(pkgincludedir)/http-parser
httpparser_HEADERS = http-parser/http_parser.h
