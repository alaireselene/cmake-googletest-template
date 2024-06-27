#include "bigint.hpp"

// Convert a BigInt to string
std::string BigInt::toString() const {
  std::string result;
  if (isNegative) {
    result.push_back('-');
  }
  for (digit d : digits) {
    result.push_back(d + '0');
  }
  return result;
}