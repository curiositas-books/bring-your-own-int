#pragma once

#include "curiositas/Types.hpp"
#include <vector>

namespace curiositas::container {

class BitVector {
public:
  BitVector() = default;

  /// Construct a @c BitVector with initial size of at least @c length bits.
  /// All values are set to @c initialValue.
  BitVector(usize length, bool initialValue);

  [[nodiscard]] auto begin() const noexcept { return _data.begin(); }
  [[nodiscard]] auto end() const noexcept { return _data.end(); }
  [[nodiscard]] auto rbegin() const noexcept { return _data.rbegin(); }
  [[nodiscard]] auto rend() const noexcept { return _data.rend(); }

  /// Return the current number of bits managed by the vector.
  [[nodiscard]] usize size() const noexcept { return _data.size(); }

  /// Return the bit at any position.
  [[nodiscard]] bool get(usize index) const { return _data.at(index) == 1U; }

  /// Provide access to the bit at any position.
  void set(usize index, bool value) { _data.at(index) = value ? 1U : 0U; }

  /// Append a new bit to the end of the vector.
  void push_back(bool bit) { _data.push_back(bit ? 1U : 0U); }

  /// Removes leading zeros from the @c BitVector.
  void normalize();

  /// Shift all bits left by @c i position(s). The new bit(s) is/are inserted at
  /// index 0 and have the value @c false. All old bits increase their index by
  /// @c i.
  /// @note If @c i equals zero the operation is a no-op.
  /// @warn Invalidates all iterators.
  /// @post VectorBefore.size() + i == VectorAfter.size()
  BitVector &operator<<=(usize i);

  /// Shift all bits right by @c i position(s). No new bits are inserted and @c
  /// i bits are dropped.
  /// @note If @c i equals zero the operation is a no-op.
  /// @note If @c i is bigger than @c size(), all bits are cleared.
  /// @warn Invalidates all iterators.
  /// @post VectorAfter.size() == max(VectorBefore.size() - i, 0)
  BitVector &operator>>=(usize i);

private:
  std::vector<u8> _data;
};
} // namespace curiositas::container
