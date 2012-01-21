# httpxx library.

set(headers
  Error.hpp
  Flags.hpp
  Message.hpp
  Method.hpp
  Request.hpp
  Response.hpp
)
set(sources
  Error.cpp
  Flags.cpp
  Message.cpp
  Method.cpp
  Request.cpp
  Response.cpp
)
add_library(httpxx
  STATIC
  ${sources}
  ${headers}
)
add_dependencies(httpxx http-parser)
