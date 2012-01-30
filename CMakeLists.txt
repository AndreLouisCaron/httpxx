#
# C++ wrappers for C-based HTTP parser library.
#

cmake_minimum_required(VERSION 2.6)

project(httpxx)

# Compile API documentation from source code.
function(add_api_documentation target)
  if(DOXYGEN_EXECUTABLE)
    add_custom_target(
      ${target}
      COMMAND
        ${DOXYGEN_EXECUTABLE}
      WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT
        "Compiling documentation."
      VERBATIM
    )
  endif()
endfunction()

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/http-parser)

# http-parser does not provide a CMake build script.
set(http_parser_DIR
   ${CMAKE_SOURCE_DIR}/libs/http-parser
)
set(http-parser_headers ${http_parser_DIR}/http_parser.h)
set(http-parser_sources ${http_parser_DIR}/http_parser.c)
if(MSVC)
  # MSVC does not support C99, but its C++ compiler is
  # compatible with the http-parser library's code.
  set_source_files_properties(
    ${http-parser_headers}
    ${http-parser_sources}
    PROPERTIES LANGUAGE CXX
  )
endif()
add_library(http-parser
  STATIC
  ${http-parser_headers}
  ${http-parser_sources}
)

# Build the primary target.
add_subdirectory(code)

# When building in standalone mode, build demo projects.
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})

  # Build API documentation.
  find_package(Doxygen QUIET)
  configure_file(
    ${CMAKE_SOURCE_DIR}/help/Doxyfile
    ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
  add_api_documentation(doc)

  # Resolve include directives as if installed on the system.
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/code)

  add_subdirectory(test)

endif()
