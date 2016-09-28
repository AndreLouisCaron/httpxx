# sha1 library demo projects.

macro(add_test_program name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} httpxx)
  add_dependencies(${name} httpxx)

  # Make the program easily accessible.
  set(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name})
endmacro()

add_test_program(http-extract-request-header)
add_test_program(http-extract-response-header)
add_test_program(http-extract-request-body)
add_test_program(http-extract-response-body)
add_test_program(pipelined-headers)
add_test_program(userbufferedmessage)

# Test cases.
set(test-data ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(minimalist-test-1
  "${http-extract-request-header}"
  "Host"
  "${test-data}/request-001.txt"
)
set_tests_properties(minimalist-test-1
  PROPERTIES PASS_REGULAR_EXPRESSION "www\\.example\\.com")

add_test(minimalist-test-2
  "${http-extract-response-header}"
  "Content-Type"
  "${test-data}/response-001.txt"
)
set_tests_properties(minimalist-test-2
  PROPERTIES PASS_REGULAR_EXPRESSION "text/plain")

add_test(minimalist-test-3
  "${http-extract-response-body}"
  "${test-data}/response-001.txt"
)
set_tests_properties(minimalist-test-3
  PROPERTIES PASS_REGULAR_EXPRESSION "Hello, world!")

add_test(pipelined-headers "${pipelined-headers}")

add_test(userbufferedmessage "${userbufferedmessage}")
