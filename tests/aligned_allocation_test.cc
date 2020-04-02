#include "gtest/gtest.h"

#include "bas/aligned_allocation.h"

using namespace bas;

static void test_aligned_allocation(size_t alignment)
{
    void *ptr1 = aligned_malloc(1, alignment);
    void *ptr2 = aligned_malloc(alignment * 32, alignment);
    void *ptr3 = aligned_malloc(71, alignment);

    EXPECT_TRUE(is_aligned(ptr1, alignment));
    EXPECT_TRUE(is_aligned(ptr2, alignment));
    EXPECT_TRUE(is_aligned(ptr3, alignment));

    aligned_free(ptr1);
    aligned_free(ptr2);
    aligned_free(ptr3);
}

static void test_aligned_allocation_fallback(size_t alignment)
{
    void *ptr1 = aligned_malloc_fallback(1, alignment);
    void *ptr2 = aligned_malloc_fallback(alignment * 32, alignment);
    void *ptr3 = aligned_malloc_fallback(71, alignment);

    EXPECT_TRUE(is_aligned(ptr1, alignment));
    EXPECT_TRUE(is_aligned(ptr2, alignment));
    EXPECT_TRUE(is_aligned(ptr3, alignment));

    aligned_free_fallback(ptr1);
    aligned_free_fallback(ptr2);
    aligned_free_fallback(ptr3);
}

TEST(aligned_allocation, AlignedAllocation)
{
    for (size_t alignment = 1; alignment < 32768; alignment *= 2) {
        test_aligned_allocation(alignment);
    }
}

TEST(aligned_allocation, AlignedAllocationFallback)
{
    for (size_t alignment = 1; alignment < 32768; alignment *= 2) {
        test_aligned_allocation_fallback(alignment);
    }
}
