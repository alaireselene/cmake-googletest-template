#include "bigint.hpp"

BigInt BigInt::operator+(const BigInt &other) const {
  BigInt result;

  if (isNegative == other.isNegative) {
    result.digits = add(digits, other.digits);
    result.isNegative = isNegative;
  } else {
    if (greater(digits, other.digits)) {
      result.digits = add(digits, other.digits, true);
      result.isNegative = isNegative;
    } else {
      result.digits = add(other.digits, digits, true);
      result.isNegative = other.isNegative;
    }
  }
  return result;
}

BigInt BigInt::operator-(const BigInt &other) const {
  BigInt result;

  if (isNegative != other.isNegative) {
    result.digits = add(digits, other.digits);
    result.isNegative = isNegative;
  } else {
    if (greater(digits, other.digits)) {
      result.digits = add(digits, other.digits, true);
      result.isNegative = isNegative;
    } else {
      result.digits = add(other.digits, digits, true);
      result.isNegative = !(other.isNegative);
    }
  }
  return result.digits.size() == 1 && result.digits.front() == 0 ? BigInt(0)
                                                                 : result;
}

BigInt BigInt::operator*(const BigInt &other) const {
  std::deque<digit> result = multiply(digits, other.digits);
  return result.size() == 1 && result.front() == 0
             ? BigInt(0)
             : BigInt(result, isNegative == other.isNegative ? false : true);
}

BigInt BigInt::operator/(const BigInt &other) const {
  std::deque<digit> result =
      divideWithRemainder(this->digits, other.digits).first;
  return result.size() == 1 && result.front() == 0
             ? BigInt(0)
             : BigInt(result, isNegative == other.isNegative ? false : true);
}

BigInt BigInt::operator%(const BigInt &other) const {
  std::deque<digit> result =
      divideWithRemainder(this->digits, other.digits).second;
  return result.size() == 1 && result.front() == 0
             ? BigInt(0)
             : BigInt(result, isNegative == other.isNegative ? false : true);
}

BigInt BigInt::operator+(const long long &other) const {
  return *this + BigInt(other);
}

BigInt BigInt::operator-(const long long &other) const {
  return *this - BigInt(other);
}

BigInt BigInt::operator*(const long long &other) const {
  return *this * BigInt(other);
}

BigInt BigInt::operator/(const long long &other) const {
  return *this / BigInt(other);
}

BigInt BigInt::operator%(const long long &other) const {
  return *this % BigInt(other);
}

BigInt BigInt::operator+(const std::string &other) const {
  return *this + BigInt(other);
}

BigInt BigInt::operator-(const std::string &other) const {
  return *this - BigInt(other);
}

BigInt BigInt::operator*(const std::string &other) const {
  return *this * BigInt(other);
}

BigInt BigInt::operator/(const std::string &other) const {
  return *this / BigInt(other);
}

BigInt BigInt::operator%(const std::string &other) const {
  return *this % BigInt(other);
}