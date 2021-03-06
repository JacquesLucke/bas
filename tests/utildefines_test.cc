#include "gtest/gtest.h"

#include "bas/utildefines.h"

#include <typeinfo>

using namespace bas;

TEST(util, IsPowerOf2)
{
    EXPECT_TRUE(is_power_of_2(0));
    EXPECT_TRUE(is_power_of_2(1));
    EXPECT_TRUE(is_power_of_2(2));
    EXPECT_TRUE(is_power_of_2(4));
    EXPECT_TRUE(is_power_of_2(8));
    EXPECT_TRUE(is_power_of_2(256));

    EXPECT_FALSE(is_power_of_2(3));
    EXPECT_FALSE(is_power_of_2(5));
    EXPECT_FALSE(is_power_of_2(255));
    EXPECT_FALSE(is_power_of_2(257));
}

TEST(util, CeilPowerOf2_u32)
{
    EXPECT_EQ(ceil_power_of_2<uint32_t>(1), (uint32_t)1);
    EXPECT_EQ(ceil_power_of_2<uint32_t>(5), (uint32_t)8);
    EXPECT_EQ(ceil_power_of_2<uint32_t>(0), (uint32_t)0);
    EXPECT_EQ(ceil_power_of_2<uint32_t>(20), (uint32_t)32);
}

TEST(util, CeilPowerOf2_u64)
{
    EXPECT_EQ(ceil_power_of_2<uint64_t>(1), (uint64_t)1);
    EXPECT_EQ(ceil_power_of_2<uint64_t>(5), (uint64_t)8);
    EXPECT_EQ(ceil_power_of_2<uint64_t>(0), (uint64_t)0);
    EXPECT_EQ(ceil_power_of_2<uint64_t>(20), (uint64_t)32);
}

TEST(util, CeilPowerOf2_sizet)
{
    EXPECT_EQ(ceil_power_of_2<size_t>(1), (size_t)1);
    EXPECT_EQ(ceil_power_of_2<size_t>(5), (size_t)8);
    EXPECT_EQ(ceil_power_of_2<size_t>(0), (size_t)0);
    EXPECT_EQ(ceil_power_of_2<size_t>(20), (size_t)32);
}

TEST(util, FloorPowerOf2)
{
    EXPECT_EQ(floor_power_of_2<uint32_t>(0), (uint32_t)0);
    EXPECT_EQ(floor_power_of_2<uint32_t>(1), (uint32_t)1);
    EXPECT_EQ(floor_power_of_2<uint32_t>(2), (uint32_t)2);
    EXPECT_EQ(floor_power_of_2<uint32_t>(3), (uint32_t)2);
    EXPECT_EQ(floor_power_of_2<uint32_t>(4), (uint32_t)4);
    EXPECT_EQ(floor_power_of_2<uint32_t>(5), (uint32_t)4);
    EXPECT_EQ(floor_power_of_2<uint32_t>(6), (uint32_t)4);
    EXPECT_EQ(floor_power_of_2<uint32_t>(7), (uint32_t)4);
    EXPECT_EQ(floor_power_of_2<uint32_t>(8), (uint32_t)8);
}

TEST(util, Log2FloorU)
{
    EXPECT_EQ(log2_floor_u(0), 0);
    EXPECT_EQ(log2_floor_u(1), 0);
    EXPECT_EQ(log2_floor_u(2), 1);
    EXPECT_EQ(log2_floor_u(3), 1);
    EXPECT_EQ(log2_floor_u(4), 2);
    EXPECT_EQ(log2_floor_u(5), 2);
    EXPECT_EQ(log2_floor_u(6), 2);
    EXPECT_EQ(log2_floor_u(7), 2);
    EXPECT_EQ(log2_floor_u(8), 3);
    EXPECT_EQ(log2_floor_u(9), 3);
    EXPECT_EQ(log2_floor_u(123456), 16);
}

TEST(util, Log2CeilU)
{
    EXPECT_EQ(log2_ceil_u(0), 0);
    EXPECT_EQ(log2_ceil_u(1), 0);
    EXPECT_EQ(log2_ceil_u(2), 1);
    EXPECT_EQ(log2_ceil_u(3), 2);
    EXPECT_EQ(log2_ceil_u(4), 2);
    EXPECT_EQ(log2_ceil_u(5), 3);
    EXPECT_EQ(log2_ceil_u(6), 3);
    EXPECT_EQ(log2_ceil_u(7), 3);
    EXPECT_EQ(log2_ceil_u(8), 3);
    EXPECT_EQ(log2_ceil_u(9), 4);
    EXPECT_EQ(log2_ceil_u(123456), 17);
}
