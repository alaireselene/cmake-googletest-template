#include "bigint.hpp"

BigInt BigInt::operator+() const { return *this; }

BigInt BigInt::operator-() const {
  BigInt result = *this;
  result.isNegative = !result.isNegative;
  return result;
}
