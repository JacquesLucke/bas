#include "gtest/gtest.h"

#include "bas/vector_set.h"

using namespace bas;

TEST(vector_set, DefaultConstructor)
{
    VectorSet<int> set;
    EXPECT_EQ(set.size(), 0u);
}

TEST(vector_set, InitializerListConstructor_WithoutDuplicates)
{
    VectorSet<int> set = {1, 4, 5};
    EXPECT_EQ(set.size(), 3u);
    EXPECT_EQ(set[0], 1);
    EXPECT_EQ(set[1], 4);
    EXPECT_EQ(set[2], 5);
}

TEST(vector_set, InitializerListConstructor_WithDuplicates)
{
    VectorSet<int> set = {1, 3, 3, 2, 1, 5};
    EXPECT_EQ(set.size(), 4u);
    EXPECT_EQ(set[0], 1);
    EXPECT_EQ(set[1], 3);
    EXPECT_EQ(set[2], 2);
    EXPECT_EQ(set[3], 5);
}

TEST(vector_set, Copy)
{
    VectorSet<int> set1 = {1, 2, 3};
    VectorSet<int> set2 = set1;
    EXPECT_EQ(set1.size(), 3u);
    EXPECT_EQ(set2.size(), 3u);
    EXPECT_EQ(set1.index(2), 1u);
    EXPECT_EQ(set2.index(2), 1u);
}

TEST(vector_set, Move)
{
    VectorSet<int> set1 = {1, 2, 3};
    VectorSet<int> set2 = std::move(set1);
    EXPECT_EQ(set1.size(), 0u);
    EXPECT_EQ(set2.size(), 3u);
}

TEST(vector_set, AddNewIncreasesSize)
{
    VectorSet<int> set;
    EXPECT_EQ(set.size(), 0u);
    set.add(5);
    EXPECT_EQ(set.size(), 1u);
}

TEST(vector_set, AddExistingDoesNotIncreaseSize)
{
    VectorSet<int> set;
    EXPECT_EQ(set.size(), 0u);
    set.add(5);
    EXPECT_EQ(set.size(), 1u);
    set.add(5);
    EXPECT_EQ(set.size(), 1u);
}

TEST(vector_set, Index)
{
    VectorSet<int> set = {3, 6, 4};
    EXPECT_EQ(set.index(6), 1u);
    EXPECT_EQ(set.index(3), 0u);
    EXPECT_EQ(set.index(4), 2u);
}

TEST(vector_set, IndexTry)
{
    VectorSet<int> set = {3, 6, 4};
    EXPECT_EQ(set.index_try(5), -1);
    EXPECT_EQ(set.index_try(3), 0);
    EXPECT_EQ(set.index_try(6), 1);
    EXPECT_EQ(set.index_try(2), -1);
}

TEST(vector_set, Remove)
{
    VectorSet<int> set = {4, 5, 6, 7};
    EXPECT_EQ(set.size(), 4u);
    set.remove(5);
    EXPECT_EQ(set.size(), 3u);
    EXPECT_EQ(set[0], 4);
    EXPECT_EQ(set[1], 7);
    EXPECT_EQ(set[2], 6);
    set.remove(6);
    EXPECT_EQ(set.size(), 2u);
    EXPECT_EQ(set[0], 4);
    EXPECT_EQ(set[1], 7);
    set.remove(4);
    EXPECT_EQ(set.size(), 1u);
    EXPECT_EQ(set[0], 7);
    set.remove(7);
    EXPECT_EQ(set.size(), 0u);
}

TEST(vector_set, UniquePtrValue)
{
    VectorSet<std::unique_ptr<int>> set;
    set.add_new(std::unique_ptr<int>(new int()));
    set.add(std::unique_ptr<int>(new int()));
    set.index_try(std::unique_ptr<int>(new int()));
    std::unique_ptr<int> value = set.pop();

    BAS_UNUSED_VAR(value);
}
