# Library configuration file used by dependent projects
# via find_package() built-in directive in "config" mode.

if(NOT DEFINED httpxx_FOUND)

  # Locate library headers.
  find_path(httpxx_include_dirs
    NAMES http.hpp
    PATHS ${httpxx_DIR}/code
  )

  # Common name for exported library targets.
  set(httpxx_libraries
    http-parser
    httpxx
    CACHE INTERNAL "httpxx library" FORCE
  )

  # Usual "required" et. al. directive logic.
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    httpxx DEFAULT_MSG
    httpxx_include_dirs
    httpxx_libraries
  )

  # Add targets to dependent project.
  add_subdirectory(
    ${httpxx_DIR}
    ${CMAKE_BINARY_DIR}/httpxx
  )
endif()
