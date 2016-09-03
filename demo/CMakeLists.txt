
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/range/include)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/euler.cpp)

add_executable(demo ${SRC})

target_link_libraries(demo)
