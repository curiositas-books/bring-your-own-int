#include "curiositas/math/SieveEratosthenes.hpp"
#include <iostream>

int main(int argc, char **argv) {
  using namespace curiositas;
  using namespace std;
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <n>\n\n"
         << "Finds the first <n> prime numbers using the sieve of "
            "eratosthenes. Each prime is printed on its own line\n";
    return EXIT_FAILURE;
  }
  auto maximumNumber = usize{stoull(argv[1])};
  for (auto const &prime : math::sieveEratosthenes(maximumNumber)) {
    cout << prime << "\n";
  }
  return EXIT_SUCCESS;
}
