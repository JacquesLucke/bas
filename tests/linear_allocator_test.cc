#include "bas/linear_allocator.h"

#include "gtest/gtest.h"

using namespace bas;

TEST(linear_allocator, AllocationAlignment)
{
    LinearAllocator<> allocator;

    EXPECT_TRUE(is_aligned(allocator.allocate(10, 4), 4));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 4), 4));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 4), 4));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 8), 8));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 4), 4));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 16), 16));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 4), 4));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 64), 64));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 64), 64));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 8), 8));
    EXPECT_TRUE(is_aligned(allocator.allocate(10, 128), 128));
}

TEST(linear_allocator, PackedAllocation)
{
    LinearAllocator<> allocator;
    AlignedBuffer<256, 32> buffer;
    allocator.provide_buffer(buffer);

    uintptr_t ptr1 = (uintptr_t)allocator.allocate(10, 4); /*  0 - 10 */
    uintptr_t ptr2 = (uintptr_t)allocator.allocate(10, 4); /* 12 - 22 */
    uintptr_t ptr3 = (uintptr_t)allocator.allocate(8, 32); /* 32 - 40 */
    uintptr_t ptr4 = (uintptr_t)allocator.allocate(16, 8); /* 40 - 56 */
    uintptr_t ptr5 = (uintptr_t)allocator.allocate(1, 8);  /* 56 - 57 */
    uintptr_t ptr6 = (uintptr_t)allocator.allocate(1, 4);  /* 60 - 61 */
    uintptr_t ptr7 = (uintptr_t)allocator.allocate(1, 1);  /* 61 - 62 */

    EXPECT_EQ(ptr2 - ptr1, 12); /* 12 -  0 = 12 */
    EXPECT_EQ(ptr3 - ptr2, 20); /* 32 - 12 = 20 */
    EXPECT_EQ(ptr4 - ptr3, 8);  /* 40 - 32 =  8 */
    EXPECT_EQ(ptr5 - ptr4, 16); /* 56 - 40 = 16 */
    EXPECT_EQ(ptr6 - ptr5, 4);  /* 60 - 56 =  4 */
    EXPECT_EQ(ptr7 - ptr6, 1);  /* 61 - 60 =  1 */
}

TEST(linear_allocator, CopyString)
{
    LinearAllocator<> allocator;
    AlignedBuffer<256, 1> buffer;
    allocator.provide_buffer(buffer);

    StringRefNull ref1 = allocator.copy_string("Hello");
    StringRefNull ref2 = allocator.copy_string("World");

    EXPECT_EQ(ref1, "Hello");
    EXPECT_EQ(ref2, "World");
    EXPECT_EQ(ref2.data() - ref1.data(), 6);
}
