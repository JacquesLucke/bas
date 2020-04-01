cmake_minimum_required(VERSION 3.5)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "in-source builds are not allowed")
endif()

project(my_core_lib)
set(CMAKE_CXX_STANDARD 17)

SET(SOURCE
    tests/test_main.cc

    tests/allocator_test.cc
    tests/array_ref_test.cc
    tests/index_range_test.cc
)

set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(extern/googletest)

include_directories(
    extern/googletest/googletest/include/

    include/
)

add_executable(tests ${SOURCE})
target_link_libraries(tests gtest)
