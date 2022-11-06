#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "curiositas/math/BigUInt.hpp"

using namespace curiositas;
using namespace curiositas::math;

TEST_CASE("Efficiency BigUInt", "[.benchmark]") {
  // Random numbers with specific bit length to check scaling by length.
  auto const n_2bit  = 3_N;
  auto const n_4bit  = 12_N;
  auto const n_8bit  = 242_N;
  auto const n_10bit = 867_N;
  auto const n_13bit = 5197_N;
  auto const n_16bit = 54461_N;

  SECTION("Comparison") {
    BENCHMARK("2bit") { return n_2bit == n_2bit; };
    BENCHMARK("4bit") { return n_4bit == n_4bit; };
    BENCHMARK("8bit") { return n_8bit == n_8bit; };
    BENCHMARK("10bit") { return n_10bit == n_10bit; };
    BENCHMARK("13bit") { return n_13bit == n_13bit; };
    BENCHMARK("16bit") { return n_16bit == n_16bit; };
  }
  SECTION("Addition") {
    BENCHMARK("2bit") { return n_2bit + n_2bit; };
    BENCHMARK("4bit") { return n_4bit + n_4bit; };
    BENCHMARK("8bit") { return n_8bit + n_8bit; };
    BENCHMARK("10bit") { return n_10bit + n_10bit; };
    BENCHMARK("13bit") { return n_13bit + n_13bit; };
    BENCHMARK("16bit") { return n_16bit + n_16bit; };
  }
  SECTION("Multiplication") {
    BENCHMARK("2bit") { return n_2bit * n_2bit; };
    BENCHMARK("4bit") { return n_4bit * n_4bit; };
    BENCHMARK("8bit") { return n_8bit * n_8bit; };
    BENCHMARK("10bit") { return n_10bit * n_10bit; };
    BENCHMARK("10bit x 2bit") { return n_10bit * n_2bit; };
    BENCHMARK("10bit x 4bit") { return n_10bit * n_4bit; };
    BENCHMARK("13bit") { return n_13bit * n_13bit; };
    BENCHMARK("13bit x 2bit") { return n_13bit * n_2bit; };
    BENCHMARK("13bit x 4bit") { return n_13bit * n_4bit; };
    BENCHMARK("13bit x 8bit") { return n_13bit * n_8bit; };
    BENCHMARK("16bit") { return n_16bit * n_16bit; };
  }
  SECTION("Division") {
    BENCHMARK("2bit") { return n_2bit / n_2bit; };
    BENCHMARK("4bit") { return n_4bit / n_4bit; };
    BENCHMARK("8bit") { return n_8bit / n_8bit; };
    BENCHMARK("10bit") { return n_10bit / n_10bit; };
    BENCHMARK("10bit / 2bit") { return n_10bit / n_2bit; };
    BENCHMARK("10bit / 4bit") { return n_10bit / n_4bit; };
    BENCHMARK("13bit") { return n_13bit / n_13bit; };
    BENCHMARK("13bit / 2bit") { return n_13bit / n_2bit; };
    BENCHMARK("13bit / 4bit") { return n_13bit / n_4bit; };
    BENCHMARK("13bit / 8bit") { return n_13bit / n_8bit; };
    BENCHMARK("16bit") { return n_16bit / n_16bit; };
  }
  SECTION("Exponentiation") {
    BENCHMARK("2bit") { return pow(n_2bit, n_2bit); };
    BENCHMARK("2bit ^  8bit") { return pow(n_2bit, n_8bit); };
    BENCHMARK("2bit ^ 10bit") { return pow(n_2bit, n_10bit); };
    BENCHMARK("2bit ^ 13bit") { return pow(n_2bit, n_13bit); };
    BENCHMARK("4bit") { return pow(n_4bit, n_4bit); };
    BENCHMARK("4bit ^ 8bit") { return pow(n_4bit, n_8bit); };
    BENCHMARK("8bit") { return pow(n_8bit, n_8bit); };
    BENCHMARK("8bit ^ 4bit") { return pow(n_8bit, n_4bit); };
    BENCHMARK("10bit ^ 2bit") { return pow(n_10bit, n_2bit); };
    BENCHMARK("10bit ^ 4bit") { return pow(n_10bit, n_4bit); };
    BENCHMARK("10bit ^ 8bit") { return pow(n_10bit, n_8bit); };
    BENCHMARK("10bit") { return pow(n_10bit, n_10bit); };
    BENCHMARK("13bit ^  2bit") { return pow(n_13bit, n_2bit); };
    BENCHMARK("13bit ^  4bit") { return pow(n_13bit, n_4bit); };
    BENCHMARK("13bit ^  8bit") { return pow(n_13bit, n_8bit); };
    BENCHMARK("13bit ^ 10bit") { return pow(n_13bit, n_10bit); };
    BENCHMARK("16bit ^  2bit") { return pow(n_16bit, n_2bit); };
    BENCHMARK("16bit ^  4bit") { return pow(n_16bit, n_4bit); };
    BENCHMARK("16bit ^  8bit") { return pow(n_16bit, n_8bit); };
    BENCHMARK("16bit ^ 10bit") { return pow(n_16bit, n_10bit); };
    // The square-multiply can not compute these results with egyptian
    // multiplication.
    BENCHMARK("13bit") { return pow(n_13bit, n_13bit); };
    // BENCHMARK("16bit ^ 13bit") { return pow(n_16bit, n_13bit); };
    // BENCHMARK("16bit") { return pow(n_16bit, n_16bit); };
  }
}
TEST_CASE("Scaling BigUInt", "[.benchmark]") {
  // Random numbers with specific bit length to check scaling over wide ranges.
  auto const n_2bit    = 3_N;
  auto const n_4bit    = 12_N;
  auto const n_8bit    = 242_N;
  auto const n_16bit   = 54461_N;
  auto const n_32bit   = 3663955456_N;
  auto const n_64bit   = 15424542443806940999_N;
  auto const n_128bit  = "305469607226988664654549275168086181819"_N;
  auto const n_256bit  = "10018792480178037378380338021043548098637989315616914"
                         "1927229883254369780795894"_N;
  auto const n_512bit  = "71553105840472600327415605407837626228472722756324"
                         "34118985227126508200777747112342538403190493596872"
                         "46356277151493669436918855437814605430187470129332"
                         "8999"_N;
  auto const n_1024bit = "164019732185557592211847196742840810864553346192188"
                         "291597812666512355161993987333573482451553056484791"
                         "568950043811061133911014347412943837804602973190416"
                         "032259998507956862741118579232443063394060047841750"
                         "408129025575150978194705752902523667260760515546025"
                         "742060761878588539319214184975265377855587711161921"
                         "099"_N;

  SECTION("Comparison") {
    BENCHMARK("   2bit") { return n_2bit == n_2bit; };
    BENCHMARK("   4bit") { return n_4bit == n_4bit; };
    BENCHMARK("   8bit") { return n_8bit == n_8bit; };
    BENCHMARK("  16bit") { return n_16bit == n_16bit; };
    BENCHMARK("  32bit") { return n_32bit == n_32bit; };
    BENCHMARK("  64bit") { return n_64bit == n_64bit; };
    BENCHMARK(" 128bit") { return n_128bit == n_128bit; };
    BENCHMARK(" 256bit") { return n_256bit == n_256bit; };
    BENCHMARK(" 512bit") { return n_512bit == n_512bit; };
    BENCHMARK("1024bit") { return n_1024bit == n_1024bit; };
  }
  SECTION("Addition") {
    BENCHMARK("   2bit") { return n_2bit + n_2bit; };
    BENCHMARK("   4bit") { return n_4bit + n_4bit; };
    BENCHMARK("   8bit") { return n_8bit + n_8bit; };
    BENCHMARK("  16bit") { return n_16bit + n_16bit; };
    BENCHMARK("  32bit") { return n_32bit + n_32bit; };
    BENCHMARK("  64bit") { return n_64bit + n_64bit; };
    BENCHMARK(" 128bit") { return n_128bit + n_128bit; };
    BENCHMARK(" 256bit") { return n_256bit + n_256bit; };
    BENCHMARK(" 512bit") { return n_512bit + n_512bit; };
    BENCHMARK("1024bit") { return n_1024bit + n_1024bit; };
  }
  SECTION("Multiplication") {
    BENCHMARK("   2bit") { return n_2bit * n_2bit; };
    BENCHMARK("   4bit") { return n_4bit * n_4bit; };
    BENCHMARK("   8bit") { return n_8bit * n_8bit; };
    BENCHMARK("  16bit") { return n_16bit * n_16bit; };
    BENCHMARK("  32bit") { return n_32bit * n_32bit; };
    BENCHMARK("  64bit") { return n_64bit * n_64bit; };
    BENCHMARK(" 128bit") { return n_128bit * n_128bit; };
    BENCHMARK(" 256bit") { return n_256bit * n_256bit; };
    BENCHMARK(" 512bit") { return n_512bit * n_512bit; };
    BENCHMARK("1024bit") { return n_1024bit * n_1024bit; };
  }
  SECTION("Division") {
    BENCHMARK("   2bit") { return n_2bit / n_2bit; };
    BENCHMARK("   4bit") { return n_4bit / n_2bit; };
    BENCHMARK("   8bit") { return n_8bit / n_2bit; };
    BENCHMARK("  16bit") { return n_16bit / n_2bit; };
    BENCHMARK("  32bit") { return n_32bit / n_2bit; };
    BENCHMARK("  64bit") { return n_64bit / n_2bit; };
    BENCHMARK(" 128bit") { return n_128bit / n_2bit; };
    BENCHMARK(" 256bit") { return n_256bit / n_2bit; };
    BENCHMARK(" 512bit") { return n_512bit / n_2bit; };
    BENCHMARK("1024bit") { return n_1024bit / n_2bit; };
  }
  SECTION("Exponentiation") {
    auto const n_9bit  = 414_N;
    auto const n_10bit = 867_N;
    auto const n_11bit = 1451_N;
    auto const n_12bit = 3488_N;
    auto const n_13bit = 5197_N;
    auto const n_14bit = 16196_N;
    BENCHMARK(" 2bit") { return pow(n_2bit, n_2bit); };
    BENCHMARK(" 4bit") { return pow(n_2bit, n_4bit); };
    BENCHMARK(" 8bit") { return pow(n_2bit, n_8bit); };
    BENCHMARK(" 9bit") { return pow(n_2bit, n_9bit); };
    BENCHMARK("10bit") { return pow(n_2bit, n_10bit); };
    BENCHMARK("11bit") { return pow(n_2bit, n_11bit); };
    BENCHMARK("12bit") { return pow(n_2bit, n_12bit); };
    BENCHMARK("13bit") { return pow(n_2bit, n_13bit); };
    BENCHMARK("14bit") { return pow(n_2bit, n_14bit); };
  }
}
