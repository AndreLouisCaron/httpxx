# http-parser does not provide a CMake build script

set(http-parser_headers http-parser/http_parser.h)
set(http-parser_sources http-parser/http_parser.c)
if(MSVC)
  # MSVC does not support C99, but its C++ compiler is
  # compatible with the http-parser library's code.
  set_source_files_properties(
    ${http-parser_headers}
    ${http-parser_sources}
    PROPERTIES LANGUAGE CXX
  )
endif()

install(FILES ${http-parser_headers} DESTINATION include/httpxx/http-parser
  COMPONENT dev)

# httpxx library

set(headers
  BufferedMessage.hpp
  UserBufferedMessage.hpp
  Error.hpp
  Flags.hpp
  icompare.hpp
  Message.hpp
  MessageBuilder.hpp
  Method.hpp
  Request.hpp
  RequestBuilder.hpp
  Response.hpp
  ResponseBuilder.hpp
  Url.hpp
)
set(sources
  Error.cpp
  Flags.cpp
  icompare.cpp
  Message.cpp
  MessageBuilder.cpp
  Method.cpp
  Request.cpp
  RequestBuilder.cpp
  Response.cpp
  ResponseBuilder.cpp
  Url.cpp
  http-parser/http_parser.c
)
add_library(httpxx
  STATIC
  ${sources}
  ${headers}
)

install(TARGETS httpxx
  EXPORT httpxxTargets
  ARCHIVE DESTINATION lib COMPONENT dev
  RUNTIME DESTINATION bin COMPONENT lib
  LIBRARY DESTINATION lib COMPONENT lib)
install(FILES ${headers} DESTINATION include/httpxx COMPONENT dev)
