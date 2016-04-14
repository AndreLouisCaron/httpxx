#
# C++ wrappers for C-based HTTP parser library.
#

cmake_minimum_required(VERSION 2.6)
if(CMAKE_VERSION VERSION_LESS 3.0)
  project(httpxx)
else()
  cmake_policy(SET CMP0048 NEW)
  project(httpxx VERSION 0.1.0)
endif()

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

# Resolve include directives as if installed on the system.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Build the primary target.
add_subdirectory(httpxx)

# Build API documentation.
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  configure_file(
    ${PROJECT_SOURCE_DIR}/help/Doxyfile
    ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
  add_api_documentation(doc)
endif()

add_subdirectory(test)
