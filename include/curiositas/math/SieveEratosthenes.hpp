#pragma once

#include "curiositas/Types.hpp"
#include <vector>

namespace curiositas::math {
/// Find alls primes up to @c maximum and returns them.
std::vector<usize> sieveEratosthenes(usize maximum);
} // namespace curiositas::math
