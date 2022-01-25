#pragma once

#include <variant>
#include <functional>

namespace rd {


template<typename T, typename... Func>
auto then(auto &variant, Func &&...func) {
  auto data = std::get_if<T>(&variant);
  if (data != nullptr) (std::invoke(std::forward<Func>(func), *data), ...);
}

template<typename T> auto is(auto &variant) {
  return std::get_if<T>(&variant) != nullptr;
}

}// namespace rd
