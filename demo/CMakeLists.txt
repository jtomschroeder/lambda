
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lambda
                    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/range/include)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/euler.cpp)

add_executable(demo_lambda ${SRC})

target_link_libraries(demo_lambda)

add_custom_target(demo
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/demo_lambda
                  COMMENT "Run demo!"
                  USES_TERMINAL
                  DEPENDS demo_lambda)
