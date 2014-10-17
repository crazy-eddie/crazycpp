cmake_minimum_required(VERSION 2.6)

project(20140810-unittest)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++1y -Wall -pedantic")

enable_testing()
include(CTest)

add_subdirectory(test)
add_subdirectory(src)