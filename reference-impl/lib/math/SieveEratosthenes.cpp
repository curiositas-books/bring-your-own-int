#include "curiositas/math/SieveEratosthenes.hpp"
#include "curiositas/container/BitVector.hpp"
#include <cassert>

namespace curiositas::math {
std::vector<usize> sieveEratosthenes(usize maximum) {
  auto primes = std::vector<usize>{};

  if (maximum < 2) {
    return primes;
  }

  // Initialize the sieve and consider all values except 0 and 1
  // as prime.
  auto sieve = container::BitVector{maximum, true};
  sieve.set(0, false);
  sieve.set(1, false);

  // Search for the next not-striked out index in the sieve. This is a prime
  // number, that will be used in the next iteration.
  auto const findNextPrime = [&sieve, &maximum](usize currentMinimalPrime) {
    for (auto i = currentMinimalPrime + 1; i < maximum; ++i) {
      if (sieve.get(i)) {
        return i;
      }
    }
    return usize{0};
  };

  // Initialize the search conditions.
  auto currentPrime = usize{2};
  auto primeSquared = currentPrime * currentPrime;

  while (primeSquared < maximum) {
    primes.emplace_back(currentPrime);

    // Strike out all multiples of the current prime number.
    for (auto i = usize{2}; i < maximum; ++i) {
      auto strikeOutIndex = currentPrime * i;
      if (strikeOutIndex >= maximum) {
        break;
      }
      sieve.set(strikeOutIndex, false);
    }

    currentPrime = findNextPrime(currentPrime);
    primeSquared = currentPrime * currentPrime;
    assert(currentPrime != usize{0});
  }
  do {
    primes.emplace_back(currentPrime);
  } while ((currentPrime = findNextPrime(currentPrime)) != usize{0});

  return primes;
}
} // namespace curiositas::math
