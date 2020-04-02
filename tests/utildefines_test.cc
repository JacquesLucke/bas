#include "gtest/gtest.h"

#include "bas/utildefines.h"

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
    EXPECT_EQ(ceil_power_of_2((uint32_t)1), 1);
    EXPECT_EQ(ceil_power_of_2((uint32_t)5), 8);
    EXPECT_EQ(ceil_power_of_2((uint32_t)0), 0);
    EXPECT_EQ(ceil_power_of_2((uint32_t)20), 32);
}

TEST(util, CeilPowerOf2_u64)
{
    EXPECT_EQ(ceil_power_of_2((uint64_t)1), 1);
    EXPECT_EQ(ceil_power_of_2((uint64_t)5), 8);
    EXPECT_EQ(ceil_power_of_2((uint64_t)0), 0);
    EXPECT_EQ(ceil_power_of_2((uint64_t)20), 32);
}
