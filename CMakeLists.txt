cmake_minimum_required(VERSION 3.5)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "in-source builds are not allowed")
endif()

project(bas)
set(CMAKE_CXX_STANDARD 17)

# Enable address sanitizer.
if(UNIX)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    SET(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

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
    tests/array_test.cc
    tests/index_range_test.cc
    tests/linear_allocator_test.cc
    tests/map_test.cc
    tests/multi_map_test.cc
    tests/set_test.cc
    tests/stack_test.cc
    tests/string_map_test.cc
    tests/string_ref_test.cc
    tests/utildefines_test.cc
    tests/vector_set_test.cc
    tests/vector_test.cc
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

# Generate many warnings.
if(MSVC)
  target_compile_options(tests PRIVATE /W4 /WX)
else()
  target_compile_options(tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
