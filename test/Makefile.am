if GCC
AM_CXXFLAGS = -Wall -Wextra -Wpointer-arith -fPIC
AM_CFLAGS =   -Wall -Wextra -Wpointer-arith -fPIC
AM_LDFLAGS =
endif GCC

if XLC
AM_CXXFLAGS = -brtl -qarch=com -qlibansi -qthreaded
AM_CFLAGS =   -brtl -qarch=com -qlibansi -qthreaded
AM_LDFLAGS = -brtl -expall
endif XLC

noinst_PROGRAMS = http_extract_request_header http_extract_response_header http_extract_request_body http_extract_response_body pipelined_headers userbufferedmessage

http_extract_request_header_SOURCES = http-extract-request-header.cpp
http_extract_request_header_LDADD = ../httpxx/libhttpxx.a

http_extract_response_header_SOURCES = http-extract-response-header.cpp
http_extract_response_header_LDADD = ../httpxx/libhttpxx.a

http_extract_request_body_SOURCES = http-extract-request-body.cpp
http_extract_request_body_LDADD = ../httpxx/libhttpxx.a

http_extract_response_body_SOURCES = http-extract-response-body.cpp
http_extract_response_body_LDADD = ../httpxx/libhttpxx.a

pipelined_headers_SOURCES = pipelined-headers.cpp
pipelined_headers_LDADD = ../httpxx/libhttpxx.a

userbufferedmessage_SOURCES = userbufferedmessage.cpp
userbufferedmessage_LDADD = ../httpxx/libhttpxx.a
