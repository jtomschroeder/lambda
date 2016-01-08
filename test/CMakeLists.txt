
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../vendor/googletest/googletest/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/googletest/googlemock/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

set(TESTS ${CMAKE_CURRENT_SOURCE_DIR}/test_bind.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_curry.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_lambda.cpp)

add_executable(test_lambda ${TESTS})

target_link_libraries(test_lambda gtest gmock gmock_main)

add_custom_target(verify
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_lambda
                  COMMENT "Build & Run Tests"
                  USES_TERMINAL
                  DEPENDS test_lambda)
