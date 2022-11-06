#pragma once

#include "curiositas/container/BitVector.hpp"
#include <climits>
#include <concepts>
#include <iosfwd>

namespace curiositas::math {
/// Custom type that holds an arbitrary large natural number.
class BigUInt {
public:
  BigUInt() = default;
  /// Construct the number from any unsigned integer @c value.
  explicit BigUInt(std::unsigned_integral auto value);

  /// @returns @c true when all digits are identical, otherwise @c false.
  bool operator==(BigUInt const &other) const noexcept;

  /// Determines which number is bigger or if they are equal.
  std::strong_ordering operator<=>(BigUInt const &other) const noexcept;

  /// Adds @c other to @c this.
  BigUInt &operator+=(BigUInt const &other);
  /// Subtracts @c other from @c this.
  /// @throws @c std::domain_error the result would be negative.
  BigUInt &operator-=(BigUInt const &other);
  /// Multiplies @c this by @c other.
  BigUInt &operator*=(BigUInt other);
  /// Divides @c this by @c other and discards the @c remainder.
  BigUInt &operator/=(BigUInt const &other);
  /// Divides @c this by @c other, keeping only the @c remainder.
  BigUInt &operator%=(BigUInt const &other);

  /// Returns the number of bits this number requires.
  [[nodiscard]] usize binaryDigits() const noexcept { return _bits.size(); }

  [[nodiscard]] bool  isOdd() const noexcept;
  [[nodiscard]] bool  isEven() const noexcept { return !isOdd(); }

  /// Doubles the number. Using @c double as name is not possible...
  void doubled() { _bits <<= 1; }
  /// Halfs the number but is inaccurate for odd numbers. It performs a
  /// bit-shift internally!
  /// @warn If @c isOdd() the operation is not accurate.
  void lossyHalf() { _bits >>= 1; }

private:
  /// Stores the binary digits. The index 0 is the least significant bit.
  container::BitVector _bits;
};

inline BigUInt operator+(BigUInt a, BigUInt const &b) { return a += b; }
inline BigUInt operator-(BigUInt a, BigUInt const &b) { return a -= b; }
inline BigUInt operator*(BigUInt a, BigUInt b) { return a *= std::move(b); }
inline BigUInt operator/(BigUInt a, BigUInt const &b) { return a /= b; }
inline BigUInt operator%(BigUInt a, BigUInt const &b) { return a %= b; }

/// Simplifies construction to `auto const number = 100_N`.
BigUInt operator""_N(unsigned long long literal);
/// Simplifies construction to `auto const number = "100"_N`.
BigUInt operator""_N(char const *literal, std::size_t len);

/// Prints out @c n to any output stream @c os in decimal base.
std::ostream &operator<<(std::ostream &os, BigUInt n);
/// Reads any natural number @c n from @c is in decimal base
std::istream &operator>>(std::istream &is, BigUInt &n);

/// @returns {quotient, remainder} for integer division of <tt>a / b</tt>.
std::pair<BigUInt, BigUInt> divmod(BigUInt a, BigUInt const &b);

/// Raises @c a to the power of @c b. This means multiplying @c a with itself @c
/// b times.
/// @returns <tt>a ^ b = a * a * a ... * a</tt>
BigUInt pow(BigUInt const &a, BigUInt b);

namespace details {
/// Computes <tt>product = a * b</tt> by expanding the multiplication to
/// addition of @c a with itself @c b times.
BigUInt repeated_addition(BigUInt const &a, BigUInt b);
/// Computes <tt>product = a * b</tt> by improving upon @c repeated_addition.
/// The algorithm doubles and halves the factors by shifting them whenever @c b
/// is even.
BigUInt addition_and_shifting(BigUInt a, BigUInt b);

/// Computes natural number division, also called euclidean division.
/// <tt>a / b = (a - b - b - ... - b) + remainder</tt>.
/// The number of times @c b can be subtracted from @c a is the quotient.
///
/// @note Because the division can leave a remainder, the function has a
///       different interface to @c repeated_addition.
/// @returns {quotient, remainder}
std::pair<BigUInt, BigUInt> repeated_subtraction(BigUInt a, BigUInt const &b);

/// Computes exponentiation <tt>a ^ b = a * a * ... * a</tt> by multiplying @c a
/// with itself @c b times.
BigUInt repeated_multiplication(BigUInt const &a, BigUInt b);
/// Computes exponentiation <tt>a ^ b = a * a * ... * a</tt> by using the same
/// algorithmic idea of @c addition_and_shifting and square intermediate values
/// when the exponent is even.
BigUInt square_multiply(BigUInt a, BigUInt b);

/// Computes the natural number division with remainder efficiently by
/// leveraging the same algorithmic idea as in the egyptian multiplication, but
/// "in reverse". The biggest divisor is found and subtracted repeatedly, while
/// counting the equivalent total number of subtraction with the original
/// divisor.
/// @sa repeated_subtraction
std::pair<BigUInt, BigUInt> subtraction_and_shifting(BigUInt a, BigUInt b);
} // namespace details

/// === Inline Implementation of Templates ===

BigUInt::BigUInt(std::unsigned_integral auto value)
    : _bits(sizeof(value) * CHAR_BIT, 0U) {
  for (auto i = 0U; i < CHAR_BIT * sizeof(value); ++i) {
    auto const singleDigit = static_cast<decltype(value)>(1U) << i;
    _bits.set(i, value & singleDigit);
  }
  _bits.normalize();
}
} // namespace curiositas::math
