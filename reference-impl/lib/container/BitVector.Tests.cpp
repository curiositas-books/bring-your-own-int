#include <catch2/catch.hpp>

#include "curiositas/container/BitVector.hpp"

using namespace curiositas;
using namespace curiositas::container;

TEST_CASE("BitVector Construction", "") {
  SECTION("Default Construction") {
    auto b = BitVector{};
    REQUIRE(b.size() == 0);
    b.push_back(true);
    b.push_back(false);
    b.push_back(false);
    b.push_back(true);
    REQUIRE(b.size() == 4);
    REQUIRE(b.get(0) == true);
    REQUIRE(b.get(1) == false);
    REQUIRE(b.get(2) == false);
    REQUIRE(b.get(3) == true);

    b.set(2, true);
    REQUIRE(b.get(2) == true);
  }

  SECTION("With Small Size") {
    auto const b = BitVector{7, true};
    REQUIRE(b.size() == 7);
    REQUIRE(b.get(4) == true);
  }

  SECTION("With Bigger Sizes") {
    auto const b = BitVector{214, false};
    REQUIRE(b.size() == 214);
    REQUIRE(b.get(210) == false);
  }
}
TEST_CASE("BitVector Normalization", "") {
  SECTION("No bits for all zeros") {
    auto b = BitVector{214, false};
    b.normalize();
    REQUIRE(b.size() == 0);
  }
  SECTION("Remove only leading bits") {
    auto b = BitVector{214, false};
    b.set(100, true);
    b.set(110, true);
    b.normalize();
    REQUIRE(b.size() == 111);
  }
}

TEST_CASE("BitVector Shift Left", "") {
  SECTION("Shift a single bit a few positions") {
    auto b = BitVector{1, true};
    REQUIRE(b.get(0) == true);
    REQUIRE(b.size() == 1);

    b <<= 3;
    REQUIRE(b.size() == 4);
    REQUIRE(b.get(0) == false);
    REQUIRE(b.get(1) == false);
    REQUIRE(b.get(2) == false);
    REQUIRE(b.get(3) == true);
  }
  SECTION("Shift a complex bit pattern a few position") {
    auto b = BitVector{3, true};
    b.set(1, false);
    REQUIRE(b.get(0) == true);
    REQUIRE(b.get(1) == false);
    REQUIRE(b.get(2) == true);
    REQUIRE(b.size() == 3);

    b <<= 2;
    REQUIRE(b.size() == 5);
    REQUIRE(b.get(0) == false);
    REQUIRE(b.get(1) == false);
    REQUIRE(b.get(2) == true);
    REQUIRE(b.get(3) == false);
    REQUIRE(b.get(4) == true);
  }
}
TEST_CASE("BitVector Shift Right", "") {
  SECTION("Shift a single bit right") {
    auto b = BitVector{1, true};
    b >>= 1;
    REQUIRE(b.size() == 0);
  }
  SECTION("Shift a vector by more than its size") {
    auto b = BitVector{3, true};
    b.set(1, false);
    b >>= 5;
    REQUIRE(b.size() == 0);
  }
  SECTION("Shift a vector a few digits and drop bits") {
    auto b = BitVector{5, true};
    b.set(1, false);
    b >>= 2;
    REQUIRE(b.size() == 3);
  }
}
