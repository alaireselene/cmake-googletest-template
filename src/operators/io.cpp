#include "bigint.hpp"

std::istream &operator>>(std::istream &is, BigInt &bigInt) {
  std::string input;
  is >> input;
  bigInt = BigInt(input);
  return is;
}

std::ostream &operator<<(std::ostream &os, const BigInt &bigInt) {
  os << bigInt.toString();
  return os;
}