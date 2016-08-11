
cmake_minimum_required(VERSION 2.8)

include_directories(${GTEST_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

set(BENCHMARKS ${CMAKE_CURRENT_SOURCE_DIR}/bench_lambda.cpp)

add_executable(bench_lambda ${BENCHMARKS})

target_link_libraries(bench_lambda benchmark)

add_custom_target(perf
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bench_lambda
                  COMMENT "Build & Run Benchmarks"
                  USES_TERMINAL
                  DEPENDS bench_lambda)
