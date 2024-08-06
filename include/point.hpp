#pragma once

#include <compare>

namespace snk {
template<typename T>
concept Coordinate = requires(T a, T b) {
  { a + b } -> std::same_as<T>;
  { a - b } -> std::same_as<T>;
  { ++a } -> std::same_as<T &>;
  { --a } -> std::same_as<T &>;
  { a++ } -> std::same_as<T>;
  { a-- } -> std::same_as<T>;
};

template<Coordinate CoordType> struct point {
  using coord_type = CoordType;
  coord_type x;
  coord_type y;

  constexpr point(coord_type x_, coord_type y_) : x(x_), y(y_) {}

  friend constexpr std::strong_ordering operator<=>(const point &a,
    const point &b) = default;
};

template<Coordinate CoordType>
point(CoordType x, CoordType y) -> point<CoordType>;
}// namespace snk
