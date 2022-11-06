#include "curiositas/math/BigUInt.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>

namespace curiositas::math {
bool BigUInt::operator==(BigUInt const &other) const noexcept {
  return (*this <=> other) == std::strong_ordering::equal;
}

std::strong_ordering BigUInt::operator<=>(BigUInt const &other) const noexcept {
  // The number with more digits must be greater. Otherwise the digits must be
  // compared.
  auto const digitRelation = binaryDigits() <=> other.binaryDigits();
  if (digitRelation != std::strong_ordering::equal) {
    return digitRelation;
  }
  auto const [bitThis, _] = std::mismatch(std::rbegin(_bits), std::rend(_bits),
                                          std::rbegin(other._bits));
  if (bitThis == std::rend(_bits)) {
    return std::strong_ordering::equal;
  }
  return *bitThis == false ? std::strong_ordering::less
                           : std::strong_ordering::greater;
}

BigUInt &BigUInt::operator+=(BigUInt const &other) {
  if (other.binaryDigits() == 0) {
    return *this;
  }
  if (binaryDigits() == 0) {
    *this = other;
    return *this;
  }
  // Optionally expand the storage of @c *this to accomdate all digits.
  while (other.binaryDigits() > binaryDigits()) {
    _bits.push_back(false);
  }
  // Compute the digit sum with honoring carries and shorter lengths of 'other'.
  // Make room for a final carry bit.
  _bits.push_back(false);
  auto i         = usize{0};
  auto carry     = false;
  auto nextCarry = false;
  for (; i < other.binaryDigits(); ++i) {
    auto const digitSum = other._bits.get(i) != _bits.get(i);
    nextCarry           = other._bits.get(i) && _bits.get(i);
    _bits.set(i, digitSum != carry);
    carry = nextCarry || (digitSum && carry);
  }
  for (; carry && i < binaryDigits(); ++i, carry = nextCarry) {
    nextCarry = carry && _bits.get(i);
    _bits.set(i, carry != _bits.get(i));
  }
  _bits.normalize();

  return *this;
}

BigUInt &BigUInt::operator-=(BigUInt const &other) {
  auto const magnitudeRelation = *this <=> other;
  if (magnitudeRelation == std::strong_ordering::less) {
    throw std::domain_error{"unsigned-subtraction would yield negative result"};
  }
  if (magnitudeRelation == std::strong_ordering::equal) {
    *this = 0_N;
    return *this;
  }
  if (other.binaryDigits() == 0) {
    return *this;
  }
  assert(magnitudeRelation == std::strong_ordering::greater);

  // Subtraction is the inverse of addition and instead of carrying a bit, they
  // are borrowed from the higher digit.
  auto i          = usize{0};
  auto borrow     = false;
  auto nextBorrow = false;
  for (; i < other.binaryDigits(); ++i) {
    auto const digitDifference = other._bits.get(i) != _bits.get(i);
    nextBorrow                 = other._bits.get(i) && !_bits.get(i);
    _bits.set(i, digitDifference != borrow);
    borrow = nextBorrow || (!digitDifference && borrow);
  }
  for (; borrow && i < binaryDigits(); ++i, borrow = nextBorrow) {
    nextBorrow = borrow && !_bits.get(i);
    _bits.set(i, borrow != _bits.get(i));
  }
  _bits.normalize();
  return *this;
}

BigUInt &BigUInt::operator*=(BigUInt other) {
#if 0
  *this = details::repeated_addition(*this, std::move(other));
#else
  *this = details::addition_and_shifting(*this, std::move(other));
#endif
  return *this;
}

BigUInt &BigUInt::operator/=(BigUInt const &other) {
  *this = divmod(*this, other).first;
  return *this;
}

BigUInt &BigUInt::operator%=(BigUInt const &other) {
  *this = divmod(*this, other).second;
  return *this;
}

bool BigUInt::isOdd() const noexcept {
  return binaryDigits() > 0 && _bits.get(0) == true;
}

BigUInt operator""_N(unsigned long long literal) { return BigUInt{literal}; }
BigUInt operator""_N(char const *literal, std::size_t len) {
  auto r  = 0_N;
  auto ss = std::stringstream{literal};
  ss >> r;
  return r;
}

std::ostream &operator<<(std::ostream &os, BigUInt n) {
  auto       digits = std::string{};
  auto const base   = BigUInt{10_N};
  // Read ASCII characters from @c is until no digit is left. Each digit is
  // converted to a @c BigUInt.
  while (n > 0_N) {
    auto [quotient, remainder] = divmod(n, base);
    n                          = std::move(quotient);
    if (remainder == 0_N) {
      digits.push_back('0');
    } else if (remainder == 1_N) {
      digits.push_back('1');
    } else if (remainder == 2_N) {
      digits.push_back('2');
    } else if (remainder == 3_N) {
      digits.push_back('3');
    } else if (remainder == 4_N) {
      digits.push_back('4');
    } else if (remainder == 5_N) {
      digits.push_back('5');
    } else if (remainder == 6_N) {
      digits.push_back('6');
    } else if (remainder == 7_N) {
      digits.push_back('7');
    } else if (remainder == 8_N) {
      digits.push_back('8');
    } else if (remainder == 9_N) {
      digits.push_back('9');
    } else {
      assert(false && "Unreachable");
    }
  }
  std::ranges::copy(digits | std::views::reverse,
                    std::ostream_iterator<char>{os});
  return os;
}

std::istream &operator>>(std::istream &is, BigUInt &n) {
  auto base10Digits = std::vector<BigUInt>{};
  // Read from @c is until no digit is left.
  while (std::isdigit(is.peek())) {
    base10Digits.emplace_back(static_cast<u8>(is.get() - '0'));
  }
  n                   = 0_N;
  auto const base     = 10_N;
  auto       position = 1_N;
  for (auto const &d : base10Digits | std::views::reverse) {
    n += position * d;
    position *= base;
  }
  return is;
}

std::pair<BigUInt, BigUInt> divmod(BigUInt a, BigUInt const &b) {
#if 0
  return details::repeated_subtraction(std::move(a), b);
#else
  return details::subtraction_and_shifting(std::move(a), b);
#endif
}

BigUInt pow(BigUInt const &a, BigUInt b) {
#if 0
  return details::repeated_multiplication(a, std::move(b));
#else
  return details::square_multiply(a, std::move(b));
#endif
}

namespace details {
BigUInt repeated_addition(BigUInt const &a, BigUInt b) {
  auto result = 0_N;
  if (a == 0_N) {
    return result;
  }

  while (b > 0_N) {
    result += a;
    b -= 1_N;
  }
  return result;
}
BigUInt addition_and_shifting(BigUInt a, BigUInt b) {
  auto accumulator = 0_N;
  if (a == 0_N) {
    return accumulator;
  }

  while (b > 0_N) {
    if (b.isOdd()) {
      accumulator += a;
      if (b == 1_N) {
        break;
      }
    }
    a.doubled();
    b.lossyHalf();
  }
  return accumulator;
}

std::pair<BigUInt, BigUInt> repeated_subtraction(BigUInt a, BigUInt const &b) {
  if (b == 0_N) {
    throw std::domain_error{"Division by 0"};
  }
  if (b == 1_N) {
    return {a, 0_N};
  }
  auto quotient = 0_N;
  // Subtract @c b from @c a until the result _would_ become negative.
  // At this point, @c -= throws a @c std::domain_error and the division
  // terminates.
  while (true) {
    try {
      a -= b;
      quotient += 1_N;
    } catch (std::domain_error const &e) {
      return {quotient, a};
    }
  }
}
BigUInt repeated_multiplication(BigUInt const &a, BigUInt b) {
  auto result = 1_N;
  if (a == 0_N) {
    return result;
  }

  while (b > 0_N) {
    result *= a;
    b -= 1_N;
  }
  return result;
}
BigUInt square_multiply(BigUInt a, BigUInt b) {
  auto accumulator = 1_N;
  if (a == 0_N) {
    return accumulator;
  }

  while (b > 0_N) {
    if (b.isOdd()) {
      accumulator *= a;
      if (b == 1_N) {
        break;
      }
    }
    a *= a;
    b.lossyHalf();
  }
  return accumulator;
}

std::pair<BigUInt, BigUInt> subtraction_and_shifting(BigUInt a, BigUInt b) {
  if (b == 0_N) {
    throw std::domain_error{"Division by 0"};
  }
  if (a == 0_N) {
    return {0_N, 0_N};
  }
  if (b == 1_N) {
    return {a, 0_N};
  }
  auto const cmp = a <=> b;
  if (cmp == std::strong_ordering::less) {
    return {0_N, a};
  } else if (cmp == std::strong_ordering::equal) {
    return {1_N, 0_N};
  }
  // Helper function to find the largest possible doubling for @c b to not
  // surpass @c a.
  auto largestDoubling = [&a](BigUInt b) -> BigUInt {
    while ((a - b) >= b) {
      b.doubled();
    }
    return b;
  };

  // Derive an auxiliary divisor from @c b that is as large as possible by
  // doubling @c b.
  auto auxDivisor = largestDoubling(b);
  // At this point, the quotient must be at least 1.
  auto quotient = 1_N;
  // Perform the first subtraction. This gets @c a and @c auxDivisor to a
  // similar magnitude.
  a -= auxDivisor;
  while (auxDivisor != b) {
    auxDivisor.lossyHalf();
    quotient.doubled();
    if (auxDivisor <= a) {
      a -= auxDivisor;
      quotient += 1_N;
    }
  }
  return {std::move(quotient), std::move(a)};
}
} // namespace details
} // namespace curiositas::math
