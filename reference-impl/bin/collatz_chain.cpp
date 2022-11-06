#include "curiositas/math/BigUInt.hpp"
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
  using namespace curiositas::math;
  using namespace std;
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <n>\n\n"
         << "Computes the length of the collatz chain for the input.\n";
    return EXIT_FAILURE;
  }
  auto input = 0_N;
  auto ss    = std::stringstream{argv[1]};
  ss >> input;
  auto number      = input;
  auto chainLength = 0_N;
  while (number != 1_N) {
    if (number.isEven()) {
      number /= 2_N;
    } else {
      number *= 3_N;
      number += 1_N;
    }
    chainLength += 1_N;
  }
  cout << "Chain Length for " << input << ": " << chainLength << endl;
  return EXIT_SUCCESS;
}
