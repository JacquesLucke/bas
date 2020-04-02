#include "gtest/gtest.h"

#include "bas/allocator.h"

using namespace bas;

TEST(raw_allocator, AlignedAllocation)
{
    RawAllocator allocator;

    void *ptr1 = allocator.allocate(1024, 512);
    void *ptr2 = allocator.allocate(1024, 512);
    void *ptr3 = allocator.allocate(1024, 512);

    EXPECT_TRUE(is_aligned(ptr1, 512));
    EXPECT_TRUE(is_aligned(ptr2, 512));
    EXPECT_TRUE(is_aligned(ptr3, 512));

    allocator.free(ptr1);
    allocator.free(ptr2);
    allocator.free(ptr3);
}
