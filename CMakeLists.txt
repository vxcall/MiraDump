cmake_minimum_required(VERSION 3.16)
project(GameOffsetDumper)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/toml11)

FILE(GLOB_RECURSE MAIN_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/GameOffsetDumper/*.cpp)
FILE(GLOB_RECURSE MAIN_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/GameOffsetDumper/*.h)

add_executable(GameOffsetDumper ${MAIN_SOURCE} ${MAIN_HEADER})