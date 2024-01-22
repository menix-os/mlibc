cmake_minimum_required(VERSION 3.25)
add_library(mlibc INTERFACE)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_subdirectory(string)
add_subdirectory(stdlib)

target_link_libraries(mlibc INTERFACE
	mlibc_string
	mlibc_stdlib
)