#pragma once
#include <functional>
#include <optional>
namespace rd {
template<typename T> void then(std::optional<T> &op, auto &&func) {
  if (op) { std::invoke(func, *op); }
}

template<typename T> void then(std::optional<T> const &op, auto &&func) {
  if (op) { std::invoke(func, *op); }
}
};// namespace rd
