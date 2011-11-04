#
# C++ wrappers for C-based HTTP parser library.
#

cmake_minimum_required(VERSION 2.8)

project(httpxx)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/http-parser)

file(GLOB ${PROJECT_NAME}_HEADERS code/*.hpp)
file(GLOB ${PROJECT_NAME}_SOURCES code/*.cpp)
add_library(${PROJECT_NAME} STATIC
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/http-parser/http_parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/http-parser/http_parser.c)

# When building in standalone mode, build demo projects.
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})

  # Resolve include directives as if installed on the system.
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/code)

endif()
