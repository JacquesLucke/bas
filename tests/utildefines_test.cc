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
    std::cout << sizeof(unsigned long) << '\n';
    std::cout << sizeof(uint32_t) << '\n';
    std::cout << sizeof(uint64_t) << '\n';
    std::cout << sizeof(size_t) << '\n';
    std::cout << std::is_same_v<unsigned long, size_t> << '\n';
    std::cout << std::is_same_v<uint64_t, size_t> << '\n';
    std::cout << std::is_same_v<uint64_t, unsigned long> << '\n';
    EXPECT_EQ(ceil_power_of_2<uint64_t>(1), (uint64_t)1);
    EXPECT_EQ(ceil_power_of_2<uint64_t>(5), (uint64_t)8);
    EXPECT_EQ(ceil_power_of_2<uint64_t>(0), (uint64_t)0);
    EXPECT_EQ(ceil_power_of_2<uint64_t>(20), (uint64_t)32);
}

// TEST(util, CeilPowerOf2_sizet)
// {
//     EXPECT_EQ(ceil_power_of_2<size_t>(1), (size_t)1);
//     EXPECT_EQ(ceil_power_of_2<size_t>(5), (size_t)8);
//     EXPECT_EQ(ceil_power_of_2<size_t>(0), (size_t)0);
//     EXPECT_EQ(ceil_power_of_2<size_t>(20), (size_t)32);
// }
