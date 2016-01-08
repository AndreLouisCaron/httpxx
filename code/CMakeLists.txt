# httpxx library.

set(headers
  BufferedMessage.hpp
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
)
add_library(httpxx
  STATIC
  ${sources}
  ${headers}
)
target_link_libraries(httpxx http-parser)
add_dependencies(httpxx http-parser)
install(TARGETS httpxx
  EXPORT httpxxTargets
  ARCHIVE DESTINATION lib COMPONENT dev
  RUNTIME DESTINATION bin COMPONENT lib
  LIBRARY DESTINATION lib COMPONENT lib
  INCLUDES DESTINATION include)
install(FILES ${headers} DESTINATION include/httpxx COMPONENT dev)
