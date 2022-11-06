#include "curiositas/container/BitVector.hpp"
#include <algorithm>

namespace curiositas::container {

BitVector::BitVector(usize length, bool initialValue)
    : _data(length, initialValue ? 1U : 0U) {}

void BitVector::normalize() {
  auto const itFirstOne = std::find(_data.crbegin(), _data.crend(), 1U);
  _data.erase(_data.begin() + std::distance(itFirstOne, _data.crend()),
              _data.end());
}
BitVector &BitVector::operator<<=(usize i) {
  _data.insert(_data.begin(), i, 0U);
  return *this;
}
BitVector &BitVector::operator>>=(usize i) {
  if (i >= size()) {
    _data.clear();
  } else {
    _data.erase(_data.begin(), _data.begin() + i);
  }
  return *this;
}
} // namespace curiositas::container
