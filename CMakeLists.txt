cmake_minimum_required(VERSION 3.5)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "in-source builds are not allowed")
endif()

project(my_core_lib)
set(CMAKE_CXX_STANDARD 11)

SET(SOURCE
    tests/first_test.cc
    tests/second_test.cc
)

set(INSTALL_GTEST OFF)
add_subdirectory(extern/googletest)

include_directories(
    extern/googletest/googletest/include/
)

add_executable(my_test ${SOURCE})
target_link_libraries(my_test gtest)
