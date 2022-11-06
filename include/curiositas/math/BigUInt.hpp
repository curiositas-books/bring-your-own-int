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
  /* Interface for @c BigUInt */
};

/* Free functions and operators for @c BigUInt */

namespace details {
/* Implementation details for arithmetic operations. */
} // namespace details

/// === Inline Implementation of Templates ===
} // namespace curiositas::math
