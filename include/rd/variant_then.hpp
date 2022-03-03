#pragma once

#include <boost/hof/pipable.hpp>
#include <variant>
#include <functional>

namespace rd {

template<typename Type> struct then_impl {
  auto operator()(auto variant, auto func) const -> decltype(variant) {
    auto data = std::get_if<Type>(&variant);
    if (data != nullptr) return func(std::get<Type>(std::move(variant)));
    return variant;
  }
};

template<typename Type>
inline auto const then = boost::hof::pipable(then_impl<Type>{});

template<typename T> auto is(auto &variant) {
  return std::get_if<T>(&variant) != nullptr;
}

}// namespace rd
