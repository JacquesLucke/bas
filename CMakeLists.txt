cmake_minimum_required(VERSION 3.5)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "in-source builds are not allowed")
endif()

project(bas)
set(CMAKE_CXX_STANDARD 17)

SET(BAS_INCLUDES
    include/
)

SET(BAS_SRC
    src/aligned_allocation.cc
)

SET(BAS_TEST_SRC
    ${BAS_SRC}

    tests/test_main.cc

    tests/aligned_allocation_test.cc
    tests/allocator_test.cc
    tests/array_ref_test.cc
    tests/index_range_test.cc
)

set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(extern/googletest)

include_directories(
    extern/googletest/googletest/include/

    ${BAS_INCLUDES}
)

add_executable(tests ${BAS_TEST_SRC})
target_link_libraries(tests gtest)
