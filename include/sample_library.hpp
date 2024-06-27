#ifndef BIGINT_H
#define BIGINT_H
#include <deque>
#include <iostream>
#include <string>
#include <utility>

// Define the digit [0-9] type
typedef char digit;

class BigInt {
public:
  // Constructors

  BigInt();
  BigInt(const BigInt &num);
  BigInt(long long value);
  BigInt(const std::string &str);
  BigInt(const std::deque<digit> &digits, bool isNegative);

  // Arithmetic Operators

  // Binary Operators
  BigInt operator+(const BigInt &other) const;
  BigInt operator+(const long long &other) const;
  BigInt operator+(const std::string &other) const;
  BigInt operator-(const BigInt &other) const;
  BigInt operator-(const long long &other) const;
  BigInt operator-(const std::string &other) const;
  BigInt operator*(const BigInt &other) const;
  BigInt operator*(const long long &other) const;
  BigInt operator*(const std::string &other) const;
  BigInt operator/(const BigInt &other) const;
  BigInt operator/(const long long &other) const;
  BigInt operator/(const std::string &other) const;
  BigInt operator%(const BigInt &other) const;
  BigInt operator%(const long long &other) const;
  BigInt operator%(const std::string &other) const;

  // Unary Operators
  BigInt operator+() const;
  BigInt operator-() const;

  // Comparison Operators
  bool operator==(const BigInt &other) const;
  bool operator!=(const BigInt &other) const;
  bool operator<(const BigInt &other) const;
  bool operator>(const BigInt &other) const;
  bool operator<=(const BigInt &other) const;
  bool operator>=(const BigInt &other) const;
  bool operator==(const long long &other) const;
  bool operator!=(const long long &other) const;
  bool operator<(const long long &other) const;
  bool operator>(const long long &other) const;
  bool operator<=(const long long &other) const;
  bool operator>=(const long long &other) const;
  bool operator==(const std::string &other) const;
  bool operator!=(const std::string &other) const;
  bool operator<(const std::string &other) const;
  bool operator>(const std::string &other) const;
  bool operator<=(const std::string &other) const;
  bool operator>=(const std::string &other) const;

  // Assignment Operators
  BigInt &operator+=(const BigInt &other);
  BigInt &operator-=(const BigInt &other);
  BigInt &operator*=(const BigInt &other);
  BigInt &operator/=(const BigInt &other);
  BigInt &operator%=(const BigInt &other);
  BigInt &operator+=(const long long &other);
  BigInt &operator-=(const long long &other);
  BigInt &operator*=(const long long &other);
  BigInt &operator/=(const long long &other);
  BigInt &operator%=(const long long &other);
  BigInt &operator+=(const std::string &other);
  BigInt &operator-=(const std::string &other);
  BigInt &operator*=(const std::string &other);
  BigInt &operator/=(const std::string &other);
  BigInt &operator%=(const std::string &other);

  // BigInt length
  int length() const;

  // Conversion Functions
  std::string toString() const;

  // I/O Operators
  friend std::ostream &operator<<(std::ostream &os, const BigInt &bigInt);
  friend std::istream &operator>>(std::istream &is, BigInt &bigInt);

private:
  // The digits of the BigInt
  std::deque<digit> digits;
  // Sign of the BigInt. True if negative, false otherwise.
  bool isNegative;
};

// Utility Functions

// Add two deques of digits and return sum of them. If bNeg is true, subtract b
std::deque<digit> add(const std::deque<digit> &a, const std::deque<digit> &b,
                      const bool &bNeg = false);

// Multiply two deques of digits and return product of them
std::deque<digit> multiply(const std::deque<digit> &a,
                           const std::deque<digit> &b);

// Divide two deques of digits and return quotient and remainder
std::pair<std::deque<digit>, std::deque<digit>>
divideWithRemainder(const std::deque<digit> &a, const std::deque<digit> &b);

// Find greater between two deques of digits a.k.a compare absolute values of
// two BigInts
bool greater(const std::deque<digit> &a, const std::deque<digit> &b);

// Match two deques of digits a.k.a compare absolute values of two BigInts
bool equal(const std::deque<digit> &a, const std::deque<digit> &b);
BigInt randomize(const int &size);
#endif