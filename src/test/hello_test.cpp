#include <gtest/gtest.h>

// From docs http://google.github.io/googletest/
TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "pan");
  EXPECT_EQ(7 * 6, 42);
}