#include <array>
#include <vector>

#include "gtest/gtest.h"

#include "bas/array_ref.h"

using namespace bas;

TEST(array_ref, AddConstToPointer)
{
    int a = 0;
    std::vector<int *> vec = {&a};
    ArrayRef<int *> ref = vec;
    ArrayRef<const int *> const_ref = ref;
    EXPECT_EQ(const_ref.size(), 1);
}

TEST(array_ref, IsReferencing)
{
    int array[] = {3, 5, 8};
    MutableArrayRef<int> ref(array, 3);
    EXPECT_EQ(ref.size(), 3);
    EXPECT_EQ(ref[1], 5);
    array[1] = 10;
    EXPECT_EQ(ref[1], 10);
}

TEST(array_ref, DropBack)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).drop_back(2);
    EXPECT_EQ(slice.size(), 2);
    EXPECT_EQ(slice[0], 4);
    EXPECT_EQ(slice[1], 5);
}

TEST(array_ref, DropBackAll)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).drop_back(a.size());
    EXPECT_EQ(slice.size(), 0);
}

TEST(array_ref, DropFront)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).drop_front(1);
    EXPECT_EQ(slice.size(), 3);
    EXPECT_EQ(slice[0], 5);
    EXPECT_EQ(slice[1], 6);
    EXPECT_EQ(slice[2], 7);
}

TEST(array_ref, DropFrontAll)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).drop_front(a.size());
    EXPECT_EQ(slice.size(), 0);
}

TEST(array_ref, TakeFront)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).take_front(2);
    EXPECT_EQ(slice.size(), 2);
    EXPECT_EQ(slice[0], 4);
    EXPECT_EQ(slice[1], 5);
}

TEST(array_ref, TakeBack)
{
    std::vector<int> a = {5, 6, 7, 8};
    auto slice = ArrayRef<int>(a).take_back(2);
    EXPECT_EQ(slice.size(), 2);
    EXPECT_EQ(slice[0], 7);
    EXPECT_EQ(slice[1], 8);
}

TEST(array_ref, Slice)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).slice(1, 2);
    EXPECT_EQ(slice.size(), 2);
    EXPECT_EQ(slice[0], 5);
    EXPECT_EQ(slice[1], 6);
}

TEST(array_ref, SliceEmpty)
{
    std::vector<int> a = {4, 5, 6, 7};
    auto slice = ArrayRef<int>(a).slice(2, 0);
    EXPECT_EQ(slice.size(), 0);
}

TEST(array_ref, SliceRange)
{
    std::vector<int> a = {1, 2, 3, 4, 5};
    auto slice = ArrayRef<int>(a).slice(IndexRange(2, 2));
    EXPECT_EQ(slice.size(), 2);
    EXPECT_EQ(slice[0], 3);
    EXPECT_EQ(slice[1], 4);
}

TEST(array_ref, Contains)
{
    std::vector<int> a = {4, 5, 6, 7};
    ArrayRef<int> a_ref = a;
    EXPECT_TRUE(a_ref.contains(4));
    EXPECT_TRUE(a_ref.contains(5));
    EXPECT_TRUE(a_ref.contains(6));
    EXPECT_TRUE(a_ref.contains(7));
    EXPECT_FALSE(a_ref.contains(3));
    EXPECT_FALSE(a_ref.contains(8));
}

TEST(array_ref, Count)
{
    std::vector<int> a = {2, 3, 4, 3, 3, 2, 2, 2, 2};
    ArrayRef<int> a_ref = a;
    EXPECT_EQ(a_ref.count(1), 0);
    EXPECT_EQ(a_ref.count(2), 5);
    EXPECT_EQ(a_ref.count(3), 3);
    EXPECT_EQ(a_ref.count(4), 1);
    EXPECT_EQ(a_ref.count(5), 0);
}

static void test_ref_from_initializer_list(ArrayRef<int> ref)
{
    EXPECT_EQ(ref.size(), 4);
    EXPECT_EQ(ref[0], 3);
    EXPECT_EQ(ref[1], 6);
    EXPECT_EQ(ref[2], 8);
    EXPECT_EQ(ref[3], 9);
}

TEST(array_ref, FromInitializerList)
{
    test_ref_from_initializer_list({3, 6, 8, 9});
}

TEST(array_ref, FromVector)
{
    std::vector<int> a = {1, 2, 3, 4};
    ArrayRef<int> a_ref(a);
    EXPECT_EQ(a_ref.size(), 4);
    EXPECT_EQ(a_ref[0], 1);
    EXPECT_EQ(a_ref[1], 2);
    EXPECT_EQ(a_ref[2], 3);
    EXPECT_EQ(a_ref[3], 4);
}

TEST(array_ref, FromArray)
{
    std::array<int, 2> a = {5, 6};
    ArrayRef<int> a_ref(a);
    EXPECT_EQ(a_ref.size(), 2);
    EXPECT_EQ(a_ref[0], 5);
    EXPECT_EQ(a_ref[1], 6);
}

TEST(array_ref, Fill)
{
    std::array<int, 5> a = {4, 5, 6, 7, 8};
    MutableArrayRef<int> a_ref(a);
    a_ref.fill(1);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 1);
    EXPECT_EQ(a[2], 1);
    EXPECT_EQ(a[3], 1);
    EXPECT_EQ(a[4], 1);
}

TEST(array_ref, FillIndices)
{
    std::array<int, 5> a = {0, 0, 0, 0, 0};
    MutableArrayRef<int> a_ref(a);
    a_ref.fill_indices({0, 2, 3}, 1);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[2], 1);
    EXPECT_EQ(a[3], 1);
    EXPECT_EQ(a[4], 0);
}

TEST(array_ref, CopyFrom)
{
    std::array<int, 3> a = {3, 4, 5};
    MutableArrayRef<int> a_ref(a);
    EXPECT_EQ(a[0], 3);
    EXPECT_EQ(a[1], 4);
    EXPECT_EQ(a[2], 5);
    a_ref.copy_from({1, 2, 3});
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
}

TEST(array_ref, ByteSize)
{
    std::array<int, 10> a;
    ArrayRef<int> a_ref(a);
    EXPECT_EQ(a_ref.byte_size(), sizeof(a));
    EXPECT_EQ(a_ref.byte_size(), 40);
}

TEST(array_ref, CopyTo)
{
    std::array<int, 3> a = {5, 6, 7};
    int b[3] = {0};
    ArrayRef<int> a_ref(a);
    a_ref.copy_to(b);

    EXPECT_EQ(b[0], 5);
    EXPECT_EQ(b[1], 6);
    EXPECT_EQ(b[2], 7);
}

TEST(array_ref, FirstLast)
{
    std::array<int, 4> a = {6, 7, 8, 9};
    ArrayRef<int> a_ref(a);
    EXPECT_EQ(a_ref.first(), 6);
    EXPECT_EQ(a_ref.last(), 9);
}

TEST(array_ref, FirstLast_OneElement)
{
    int a = 3;
    ArrayRef<int> a_ref(&a, 1);
    EXPECT_EQ(a_ref.first(), 3);
    EXPECT_EQ(a_ref.last(), 3);
}

TEST(array_ref, Get)
{
    std::array<int, 3> a = {5, 6, 7};
    ArrayRef<int> a_ref(a);
    EXPECT_EQ(a_ref.get(0, 42), 5);
    EXPECT_EQ(a_ref.get(1, 42), 6);
    EXPECT_EQ(a_ref.get(2, 42), 7);
    EXPECT_EQ(a_ref.get(3, 42), 42);
    EXPECT_EQ(a_ref.get(4, 42), 42);
}

TEST(array_ref, ContainsPtr)
{
    std::array<int, 3> a = {5, 6, 7};
    int other = 10;
    ArrayRef<int> a_ref(a);
    EXPECT_TRUE(a_ref.contains_ptr(&a[0] + 0));
    EXPECT_TRUE(a_ref.contains_ptr(&a[0] + 1));
    EXPECT_TRUE(a_ref.contains_ptr(&a[0] + 2));
    EXPECT_FALSE(a_ref.contains_ptr(&a[0] + 3));
    EXPECT_FALSE(a_ref.contains_ptr(&a[0] - 1));
    EXPECT_FALSE(a_ref.contains_ptr(&other));
}

TEST(array_ref, FirstIndex)
{
    std::array<int, 5> a = {4, 5, 4, 2, 5};
    ArrayRef<int> a_ref(a);

    EXPECT_EQ(a_ref.first_index(4), 0);
    EXPECT_EQ(a_ref.first_index(5), 1);
    EXPECT_EQ(a_ref.first_index(2), 3);
}

TEST(array_ref, CastSameSize)
{
    int value = 0;
    std::array<int *, 4> a = {&value, nullptr, nullptr, nullptr};
    ArrayRef<int *> a_ref = a;
    ArrayRef<float *> new_a_ref = a_ref.cast<float *>();

    EXPECT_EQ(a_ref.size(), 4);
    EXPECT_EQ(new_a_ref.size(), 4);

    EXPECT_EQ(a_ref[0], &value);
    EXPECT_EQ(new_a_ref[0], (float *)&value);
}

TEST(array_ref, CastSmallerSize)
{
    std::array<uint32_t, 4> a = {3, 4, 5, 6};
    ArrayRef<uint32_t> a_ref = a;
    ArrayRef<uint16_t> new_a_ref = a_ref.cast<uint16_t>();

    EXPECT_EQ(a_ref.size(), 4);
    EXPECT_EQ(new_a_ref.size(), 8);
}

TEST(array_ref, CastLargerSize)
{
    std::array<uint16_t, 4> a = {4, 5, 6, 7};
    ArrayRef<uint16_t> a_ref = a;
    ArrayRef<uint32_t> new_a_ref = a_ref.cast<uint32_t>();

    EXPECT_EQ(a_ref.size(), 4);
    EXPECT_EQ(new_a_ref.size(), 2);
}
