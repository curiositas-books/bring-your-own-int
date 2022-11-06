#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "curiositas/math/SieveEratosthenes.hpp"

using namespace curiositas;
using namespace curiositas::math;

TEST_CASE("Sieve Eratosthenes", "[test]") {
  SECTION("Up to 1") {
    auto const p = sieveEratosthenes(1);
    REQUIRE(p.size() == 0);
  }

  SECTION("Up to 50") {
    auto const p = sieveEratosthenes(50);
    REQUIRE(p.size() == 15);
    REQUIRE(p == std::vector<usize>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
                                    41, 43, 47});
  }
  SECTION("Counts up to specific numbers") {
    auto const p1000 = sieveEratosthenes(1'000);
    REQUIRE(p1000.size() == 168);
    REQUIRE(p1000.front() == 2);
    REQUIRE(p1000.back() == 997);

    auto const p1000000 = sieveEratosthenes(1'000'000);
    REQUIRE(p1000000.size() == 78'498);
    REQUIRE(p1000000.front() == 2);
    REQUIRE(p1000000.back() == 999'983);
  }
}

TEST_CASE("Sieve Eratosthenes Scaling", "[.benchmark]") {
  BENCHMARK("to 100") { return sieveEratosthenes(100); };
  BENCHMARK("to 1'000") { return sieveEratosthenes(1'000); };
  BENCHMARK("to 10'000") { return sieveEratosthenes(10'000); };
  BENCHMARK("to 100'000") { return sieveEratosthenes(100'000); };
  BENCHMARK("to 1'000'000") { return sieveEratosthenes(1'000'000); };
  BENCHMARK("to 10'000'000") { return sieveEratosthenes(10'000'000); };
}
