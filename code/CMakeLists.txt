# httpxx library.

set(headers
  Error.hpp
  Flags.hpp
  icompare.hpp
  Message.hpp
  Method.hpp
  Request.hpp
  Response.hpp
)
set(sources
  Error.cpp
  Flags.cpp
  icompare.cpp
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
