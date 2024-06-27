#include "bigint.hpp"

BigInt &BigInt::operator+=(const BigInt &other) {
  *this = *this + other;
  return *this;
}

BigInt &BigInt::operator+=(const long long &other) {
  *this = *this + BigInt(other);
  return *this;
}

BigInt &BigInt::operator+=(const std::string &other) {
  *this = *this + BigInt(other);
  return *this;
}

BigInt &BigInt::operator-=(const BigInt &other) {
  *this = *this - other;
  return *this;
}

BigInt &BigInt::operator-=(const long long &other) {
  *this = *this - BigInt(other);
  return *this;
}

BigInt &BigInt::operator-=(const std::string &other) {
  *this = *this - BigInt(other);
  return *this;
}

BigInt &BigInt::operator*=(const long long &other) {
  *this = *this * BigInt(other);
  return *this;
}

BigInt &BigInt::operator*=(const BigInt &other) {
  *this = *this * other;
  return *this;
}

BigInt &BigInt::operator*=(const std::string &other) {
  *this = *this * BigInt(other);
  return *this;
}

BigInt &BigInt::operator/=(const BigInt &other) {
  *this = *this / other;
  return *this;
}

BigInt &BigInt::operator/=(const long long &other) {
  *this = *this / BigInt(other);
  return *this;
}

BigInt &BigInt::operator/=(const std::string &other) {
  *this = *this / BigInt(other);
  return *this;
}
