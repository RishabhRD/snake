#pragma once

#include <concepts>
#include <vector>

namespace nostd {
// Precondition:
//   - matrix.size() > 0
// Postcontion:
//   - returns number of elements in matrix == val
template <std::equality_comparable T>
inline auto count(std::vector<std::vector<T>> const& matrix, T const& val) {
  auto const m = matrix.size();
  auto const n = matrix[0].size();
  std::size_t cnt{};
  for (std::size_t i{}; i < m; ++i) {
    for (std::size_t j{}; j < n; ++j) {
      if (matrix[i][j] == val)
        ++cnt;
    }
  }
  return cnt;
}

// Precondition:
//   - matrix.size() > 0
//   - n > 0
// Postcondition:
//   - gets nth element position that is equal to val in a row major fashion
template <std::equality_comparable T>
inline auto find_n(std::vector<std::vector<T>> const& matrix, T const& val,
                   std::size_t n) {
  auto const rows = matrix.size();
  auto const cols = matrix[0].size();
  std::size_t cnt{};
  for (std::size_t i{}; i < rows; ++i) {
    for (std::size_t j{}; j < cols; ++j) {
      if (matrix[i][j] == val) {
        ++cnt;
        if (cnt == n)
          return std::pair{i, j};
      }
    }
  }
  return std::pair{rows, cols};
}

// Precondition:
//   - matrix.size() > 0
// Postcondition:
//   - find_n with n == 1
template <std::equality_comparable T>
inline auto find(std::vector<std::vector<T>> const& matrix, T const& val) {
  return find_n(matrix, val, 1);
}
}  // namespace nostd
