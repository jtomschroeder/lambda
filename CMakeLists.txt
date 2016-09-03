
cmake_minimum_required(VERSION 2.8)
project(lambda)

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/.vendor/variant/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/demo EXCLUDE_FROM_ALL)

set(GTEST_INCLUDE_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/.vendor/googletest/googletest/include
                        ${CMAKE_CURRENT_SOURCE_DIR}/.vendor/googletest/googlemock/include
                        ${CMAKE_CURRENT_SOURCE_DIR}/.vendor/benchmark/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.vendor/googletest/googlemock EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.vendor/benchmark EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bench)
