#include "gtest/gtest.h"

TEST(my_test, FirstTest) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

TEST(my_test, FirstTest2) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
