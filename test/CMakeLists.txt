
cmake_minimum_required(VERSION 2.8)

include_directories(${GTEST_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

set(TESTS ${CMAKE_CURRENT_SOURCE_DIR}/test_bind.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_dollar.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_curry.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_maybe.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_show.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_stream.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/test_lambda.cpp)

add_executable(verify ${TESTS})

target_link_libraries(verify gtest gmock gmock_main)
