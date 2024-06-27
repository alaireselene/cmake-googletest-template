#include "sample_library.hpp"
#include <gtest/gtest.h>

TEST(NumberIntegrity, PosStr) {
  BigInt b("987654321098765432109876543210");
  EXPECT_EQ(b.toString(), "987654321098765432109876543210");
}

TEST(NumberIntegrity, NegStr) {
  BigInt b("-987654321098765432109876543210");
  EXPECT_EQ(b.toString(), "-987654321098765432109876543210");
}

TEST(NumberIntegrity, PosInt) {
  BigInt b(987654321);
  EXPECT_EQ(b.toString(), "987654321");
}

TEST(NumberIntegrity, NegInt) {
  BigInt b(-987654321);
  EXPECT_EQ(b.toString(), "-987654321");
}

TEST(Invalidate, Empty) { EXPECT_THROW(BigInt(""), std::invalid_argument); }

TEST(Invalidate, InvalidChar) {
  EXPECT_THROW(BigInt("123456 7890a"), std::invalid_argument);
}