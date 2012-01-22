# sha1 library demo projects.

macro(add_test_program name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} httpxx http-parser)
  add_dependencies(${name} httpxx http-parser)
endmacro()

add_test_program(http-extract-request-header)
add_test_program(http-extract-response-header)
add_test_program(http-extract-request-body)
add_test_program(http-extract-response-body)

# Variables for easy test case authoring.
set(extract-request-header
  ${CMAKE_CURRENT_BINARY_DIR}/http-extract-request-header
)
set(extract-response-header
  ${CMAKE_CURRENT_BINARY_DIR}/http-extract-response-header
)
set(extract-request-body
  ${CMAKE_CURRENT_BINARY_DIR}/http-extract-request-body
)
set(extract-response-body
  ${CMAKE_CURRENT_BINARY_DIR}/http-extract-response-body
)

# Test cases.
set(test-data ${CMAKE_CURRENT_SOURCE_DIR})
add_test(minimalist-test-1
  "${extract-request-header}" "Host" "${test-data}/request-001.txt")
set_tests_properties(minimalist-test-1
  PROPERTIES PASS_REGULAR_EXPRESSION "www\\.example\\.com")

add_test(minimalist-test-2
  "${extract-response-header}" "Content-Type" "${test-data}/response-001.txt")
set_tests_properties(minimalist-test-2
  PROPERTIES PASS_REGULAR_EXPRESSION "text/plain")

add_test(minimalist-test-3
  "${extract-response-body}" "${test-data}/response-001.txt")
set_tests_properties(minimalist-test-3
  PROPERTIES PASS_REGULAR_EXPRESSION "Hello, world!")
