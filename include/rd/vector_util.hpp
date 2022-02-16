#pragma once

#include <optional>
#include <vector>

template<typename T>
auto last_element(std::vector<T> const &vec) -> std::optional<T> {
  if (vec.empty()) return std::nullopt;
  return vec.back();
}
