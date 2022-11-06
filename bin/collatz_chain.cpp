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
  /* Implementation for Collatz Series */
  return EXIT_SUCCESS;
}
