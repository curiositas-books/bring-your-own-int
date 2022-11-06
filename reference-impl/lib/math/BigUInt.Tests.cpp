#include "curiositas/math/BigUInt.hpp"
#include <catch2/catch.hpp>
#include <sstream>

using namespace curiositas;
using namespace curiositas::math;

TEST_CASE("BigUInt from Builtin", "[test]") {
  SECTION("different unsigned types") {
    auto const b0 = BigUInt{u8{255}};
    REQUIRE(b0.binaryDigits() == 8);
    auto const b1 = BigUInt{u16{256}};
    REQUIRE(b1.binaryDigits() == 9);
    auto const b2 = BigUInt{u32{256}};
    REQUIRE(b2.binaryDigits() == 9);
  }
  SECTION("powers of two") {
    auto const zero = 0_N;
    REQUIRE(zero.binaryDigits() == 0);
    auto const b0 = 1_N;
    REQUIRE(b0.binaryDigits() == 1);
    auto const b1 = 2_N;
    REQUIRE(b1.binaryDigits() == 2);
    auto const b2 = 4_N;
    REQUIRE(b2.binaryDigits() == 3);
    auto const b3 = 8_N;
    REQUIRE(b3.binaryDigits() == 4);
  }
  SECTION("2^n - 1") {
    auto const b2 = 3_N;
    REQUIRE(b2.binaryDigits() == 2);
    auto const b3 = 7_N;
    REQUIRE(b3.binaryDigits() == 3);
    auto const b4 = 15_N;
    REQUIRE(b4.binaryDigits() == 4);
    auto const b5 = 31_N;
    REQUIRE(b5.binaryDigits() == 5);
    auto const b6 = 63_N;
    REQUIRE(b6.binaryDigits() == 6);
  }
}
TEST_CASE("BigUInt Equality", "[test]") {
  SECTION("Equality for identical digit count") {
    REQUIRE(0_N == 0_N);
    REQUIRE(5_N != 6_N);
    REQUIRE(2_N != 6_N);
    REQUIRE(7_N != 6_N);
  }
  SECTION("Inequality for different digit count") {
    REQUIRE(0_N != 1_N);
    REQUIRE(5_N != 248_N);
  }
}
TEST_CASE("BigUInt Magnitude Relations", "[test]") {
  SECTION("Differing DigitCount") {
    REQUIRE(0_N < 10_N);
    REQUIRE(5_N <= 10_N);
    REQUIRE(12321_N > 241_N);
    REQUIRE(1231_N >= 241_N);
  }
  SECTION("Same DigitCount") {
    REQUIRE(10_N < 11_N);
    REQUIRE(14_N < 15_N);
    REQUIRE(15_N > 12_N);
    REQUIRE(31_N > 25_N);
    REQUIRE(10_N <= 10_N);
    REQUIRE(10_N >= 10_N);
  }
}

TEST_CASE("BigUInt +=", "[test]") {
  SECTION("+= 0") {
    auto a = 10_N;
    a += 0_N;
    REQUIRE(a == 10_N);
    auto b = 0_N;
    b += 42_N;
    REQUIRE(b == 42_N);
  }
  SECTION("+= without carry") {
    auto a0 = 4_N;
    a0 += 1_N;
    REQUIRE(a0 == 5_N);
    auto a1 = 4_N;
    a1 += 2_N;
    REQUIRE(a1 == 6_N);
    auto a2 = 4_N;
    a2 += 3_N;
    REQUIRE(a2 == 7_N);
    auto a3 = 1_N;
    a3 += 4_N;
    REQUIRE(a3 == 5_N);
  }
  SECTION("+= with carry") {
    auto a0 = 5_N;
    a0 += 1_N;
    REQUIRE(a0 == 6_N);
    auto a1 = 5_N;
    a1 += 3_N;
    REQUIRE(a1 == 8_N);
    auto a2 = 5_N;
    a2 += 11_N;
    REQUIRE(a2 == 16_N);
    auto a3 = 13418912_N;
    a3 += 912421234_N;
    REQUIRE(a3 == BigUInt{13418912U + 912421234U});
  }
}

TEST_CASE("BigUInt -=", "[test]") {
  SECTION("-= special cases") {
    auto a0 = 0_N;
    a0 -= 0_N;
    REQUIRE(a0 == 0_N);
    auto a1 = 1293_N;
    a1 -= 1293_N;
    REQUIRE(a1 == 0_N);
    auto a2 = 0_N;
    REQUIRE_THROWS_AS(a2 -= 1_N, std::domain_error);
  }
  SECTION("-= all cases") {
    auto a = 6_N;
    a -= 5_N;
    REQUIRE(a == 1_N);
    auto b = 10_N;
    b -= 3_N;
    REQUIRE(b == 7_N);
    auto c = 8_N;
    c -= 1_N;
    REQUIRE(c == 7_N);
    auto d = 32_N;
    d -= 16_N;
    REQUIRE(d == 16_N);
    auto e = 31_N;
    e -= 16_N;
    REQUIRE(e == 15_N);
    auto f = 1039812_N;
    f -= 1239_N;
    REQUIRE(f == BigUInt{1039812U - 1239U});
  }
}

TEST_CASE("BigUInt +,-", "[test]") {
  auto const res = 32_N + 10_N - 15_N;
  REQUIRE(res == 27_N);
}

TEST_CASE("BigUInt *=", "[test]") {
  SECTION("naive implementation") {
    REQUIRE(462_N == details::repeated_addition(42_N, 11_N));
  }
  SECTION("*= {0,1}") {
    auto a = 42_N;
    a *= 1_N;
    REQUIRE(a == 42_N);
    a *= 0_N;
    REQUIRE(a == 0_N);
  }
  SECTION("*= anything") {
    auto a = 42_N;
    a *= 10_N;
    REQUIRE(a == 420_N);
    a *= 1_N;
    REQUIRE(a == 420_N);
    a *= 15_N;
    REQUIRE(a == 6300_N);
  }
}

TEST_CASE("BigUInt /=,%=", "[test]") {
  SECTION("generic interface") {
    REQUIRE(std::pair{6_N, 2_N} == divmod(44_N, 7_N));
  }
  SECTION("naive implementation") {
    REQUIRE(std::pair{6_N, 2_N} == details::repeated_subtraction(44_N, 7_N));
  }
  SECTION("/= {0,1}") {
    auto a = 127_N;
    REQUIRE_THROWS_AS(a /= 0_N, std::domain_error);
    a /= 1_N;
    REQUIRE(a == 127_N);
  }
  SECTION("/=") {
    auto a = 127_N;
    a /= 13_N;
    REQUIRE(a == 9_N);
    a /= 13_N;
    REQUIRE(a == 0_N);
  }
  SECTION("%=") {
    auto a = 128397_N;
    REQUIRE_THROWS_AS(a %= 0_N, std::domain_error);
    a %= 37_N;
    REQUIRE(a == 7_N);
  }
}
TEST_CASE("BigUInt Exponentiation", "[test]") {
  SECTION("generic interface") {
    REQUIRE(pow(0_N, 0_N) == 1_N);
    REQUIRE(pow(0_N, 30_N) == 1_N);
    REQUIRE(pow(10_N, 0_N) == 1_N);
    REQUIRE(pow(114_N, 1_N) == 114_N);
    REQUIRE(pow(114_N, 3_N) == 1481544_N);
    REQUIRE(pow(3_N, 20_N) == 3486784401_N);
  }
  SECTION("naive implementation") {
    REQUIRE(details::repeated_multiplication(0_N, 0_N) == 1_N);
    REQUIRE(details::repeated_multiplication(0_N, 30_N) == 1_N);
    REQUIRE(details::repeated_multiplication(10_N, 0_N) == 1_N);
    REQUIRE(details::repeated_multiplication(114_N, 1_N) == 114_N);
    REQUIRE(details::repeated_multiplication(114_N, 3_N) == 1481544_N);
    REQUIRE(details::repeated_multiplication(3_N, 20_N) == 3486784401_N);
  }
  SECTION("Square-Multiply") {
    REQUIRE(details::square_multiply(83_N, 7_N) == 27136050989627_N);
    REQUIRE(details::square_multiply(43_N, 11_N) == 929293739471222707_N);
    REQUIRE(details::square_multiply(3_N, 31_N) == 617673396283947_N);
  }
}

TEST_CASE("BigUInt input/output", "[test]") {
  auto original = 129471_N;
  auto ss       = std::stringstream{};
  ss << original;
  auto result = 0_N;
  ss >> result;
  REQUIRE(original == result);
}

TEST_CASE("BigUInt doubled/halfed", "[test]") {
  SECTION("Doubling") {
    auto n = 41_N;
    n.doubled();
    n.doubled();
    n.doubled();
    REQUIRE(n == 328_N);
  }
  SECTION("Halfing") {
    auto n = 164_N;
    n.lossyHalf();
    n.lossyHalf();
    REQUIRE(n == 41_N);
    n.lossyHalf();
    REQUIRE(n == 20_N);
  }
}
