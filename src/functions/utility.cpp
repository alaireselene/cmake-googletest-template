#include "bigint.hpp"
#include <chrono>
#include <cmath>
#include <random>

// Return length of BigInt
int BigInt::length() const { return digits.size(); }

// Add two deques of digits. If bNeg is true, subtract b from a.
std::deque<digit> add(const std::deque<digit> &a, const std::deque<digit> &b,
                      const bool &bNeg) {
  std::deque<digit> result;
  int aSize = a.size();
  int bSize = b.size();
  int carry = 0;

  for (int i = 0; i < aSize || i < bSize || carry > 0; ++i) {
    int sum = carry;
    if (i < aSize) {
      sum += a.at(aSize - 1 - i);
    }
    if (i < bSize) {
      if (bNeg) {
        sum -= b.at(bSize - 1 - i);
      } else {
        sum += b.at(bSize - 1 - i);
      }
    }
    if (sum < 0) {
      sum += 10;
      carry = -1;
    } else {
      carry = 0;
    }
    result.push_front(sum % 10);
    if (!bNeg) {
      carry = sum / 10;
    }
  }
  while (result.size() > 1 && result.front() == 0) {
    result.pop_front();
  }
  return result;
}

// Multiply two deques of digits.
std::deque<digit> multiply(const std::deque<digit> &a,
                           const std::deque<digit> &b) {
  auto start = std::chrono::high_resolution_clock::now();
  std::deque<digit> result;
  // If a or b is 0, return 0
  if ((a.size() == 1 && a.front() == 0) || (b.size() == 1 && b.front() == 0)) {
    return std::deque<digit>{0};
  }
  // If a or b is 1, return the other number
  if (a.size() == 1 && a.front() == 1) {
    return b;
  }
  if (b.size() == 1 && b.front() == 1) {
    return a;
  }
  int aSize = a.size();
  int bSize = b.size();
  // If a and b exceed limit of system, throw runtime error
  std::string dummyString;
  if (aSize + bSize > dummyString.max_size()) {
    throw std::runtime_error(
        "Multiplication exceeds system limit. Please reduce "
        "the length of a or b and try again.");
  }

  for (int i = aSize - 1; i >= 0; --i) {
    // Check if the multiplication is taking too long
    auto now = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
    if (duration.count() > 1000) {
      throw std::runtime_error("Timeout: Digits multiplication is taking too "
                               "long. Please reduce the "
                               "length of a or b and try again.");
    }

    std::deque<digit> partial;
    // Left shift the partial product by aSize - 1 - i
    partial.insert(partial.begin(), aSize - 1 - i, 0);
    int carry = 0;
    // Multiply a[i] with b and add carry
    for (int j = bSize - 1; j >= 0 || carry > 0; --j) {
      int product = carry;
      if (j >= 0) {
        product += a.at(i) * b.at(j);
      }

      partial.push_front(product % 10);
      carry = product / 10;
    }
    result = add(result, partial);
  }
  // Remove leading zeros
  while (result.size() > 1 && result.front() == 0) {
    result.pop_front();
  }
  return result;
}

// Divide two deques of digits
std::pair<std::deque<digit>, std::deque<digit>>
divideWithRemainder(const std::deque<digit> &a, const std::deque<digit> &b) {
  auto start = std::chrono::high_resolution_clock::now();
  std::deque<digit> quotient;
  std::deque<digit> remainder = a;
  int aSize = a.size();
  int bSize = b.size();

  // If b = 0 then throw logic error
  if (bSize == 1 && b.back() == 0) {
    throw std::logic_error("Undefined, attempt to divide by zero. Please enter "
                           "a non-zero divisor.");
  }
  // If a = 0 then remainder = 0 and quotient = 0
  else if (aSize == 1 && a.back() == 0) {
    quotient = std::deque<digit>{0};
    remainder = std::deque<digit>{0};
  }
  // If b = 1 then remainder = 0 and quotient = a
  else if (bSize == 1 && b.back() == 1) {
    quotient = a;
    remainder = std::deque<digit>{0};
  }

  // If a = b then remainder = 0 and quotient = 1
  else if (equal(a, b)) {
    quotient = std::deque<digit>{1};
    remainder = std::deque<digit>{0};
  }
  // If a < b then remainder = a and quotient = 0
  else if (greater(b, a)) {
    quotient = std::deque<digit>{0};
  } else {

    // Set flag to keep track of the current index of a
    int flag = bSize - 1;
    remainder.erase(remainder.begin() + bSize, remainder.end());

    for (int i = flag; i < aSize; ++i) {
      // Check if the division is taking too long
      auto now = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
      if (duration.count() > 13000) {
        throw std::runtime_error(
            "Timeout: Digits division is taking too long. Please reduce the "
            "length of a or b and try again.");
      }

      if (greater(remainder, b) || equal(remainder, b)) {
        // If temp is greater than b but with same size, guess x in [1,
        // temp.back() / b.back()] . Otherwise, guess x in [1, 9]
        digit x =
            remainder.size() == b.size() ? remainder.front() / b.front() : 9;
        while (greater(multiply(b, std::deque<digit>{x}), remainder)) {
          --x;
        }
        // Add x to quotient and subtract b * x from remainder
        quotient.push_back(x);
        remainder = add(remainder, multiply(b, std::deque<digit>{x}), true);
      }
      if (i < aSize - 1) {
        remainder.push_back(a.at(i + 1));
      }
    }
  }
  return std::make_pair(quotient, remainder);
}

// Check if a is greater than b by comparing digits.
bool greater(const std::deque<digit> &a, const std::deque<digit> &b) {
  int aSize = a.size();
  int bSize = b.size();
  if (aSize > bSize) {
    return true;
  } else if (aSize < bSize) {
    return false;
  } else {
    bool isGreater = true;
    for (int i = 0; i < aSize; ++i) {
      if (a.at(i) != b.at(i)) {
        isGreater = a.at(i) > b.at(i);
        break;
      }
    }
    return isGreater;
  }
}

// Check if a is equal to b
bool equal(const std::deque<digit> &a, const std::deque<digit> &b) {
  if (a.size() != b.size()) {
    return false;
  }
  int aSize = a.size();
  for (int i = 0; i < aSize; ++i) {
    if (a.at(i) != b.at(i)) {
      return false;
    }
  }
  return true;
}

// Generate a random BigInt with a given size
BigInt randomize(const int &size) {
  if (size <= 0) {
    throw std::invalid_argument("Size must be greater than 0.");
  }
  std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dis(0, 9);
  std::uniform_int_distribution<int> sign(0, 1);
  std::deque<char> digits;
  bool isNegative = bool(sign(gen));
  for (int i = 0; i < size; ++i) {
    digits.push_back(dis(gen));
  }

  return BigInt(digits, isNegative);
}