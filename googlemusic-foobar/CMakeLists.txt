cmake_minimum_required(VERSION 2.6)

project(googlemusic-foobar)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

add_subdirectory(foobar_SDK)
add_subdirectory(foo_gmusic)