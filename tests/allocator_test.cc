#include "gtest/gtest.h"

#include "my_core_lib/allocator.h"

using namespace my_core_lib;

TEST(raw_allocator, AlignedAllocation)
{
    void *ptr1 = RawAllocator{}.allocate(1024, 512);
    void *ptr2 = RawAllocator{}.allocate(1024, 512);
    void *ptr3 = RawAllocator{}.allocate(1024, 512);

    EXPECT_TRUE(is_aligned(ptr1, 512));
    EXPECT_TRUE(is_aligned(ptr2, 512));
    EXPECT_TRUE(is_aligned(ptr3, 512));
}
