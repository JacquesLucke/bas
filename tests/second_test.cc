#include "gtest/gtest.h"

TEST(my_test, FirstTest3) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

TEST(my_test, FirstTest4) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(true);
}
