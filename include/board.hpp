#pragma once

#include <bitset>
#include <cstddef>
#include "mod_int.hpp"
#include "point.hpp"
#include "snake.hpp"

namespace snk {
// TODO: I couldn't find any invariants this class can hold in a convincing
// way. There is surely some constraints like fruit should be inside board
// dimensions only. However, I don't know how to express them.
// Feel free to raise a PR if you can figure it out or an issue if you can
// justify the current decision :)
struct board {
  std::size_t width;
  std::size_t height;
  snk::snake<mod_int> snake;
  snk::point<std::size_t> fruit_pos;

  friend bool operator==(board const&, board const&) = default;
};

class cell_info {
  static constexpr std::size_t body = 0;
  static constexpr std::size_t head = 1;
  static constexpr std::size_t fruit = 2;

  // Class Invariants:
  //   - rep[body] represents if cell has snake body
  //   - rep[head] represents if cell has snake head
  //   - rep[fruit] represents if cell has fruit
  std::bitset<3> rep;

 public:
  auto is_empty() const noexcept { return rep.none(); }

  auto has_head() const noexcept { return rep.test(head); }

  auto has_body() const noexcept { return rep.test(body); }

  auto has_fruit() const noexcept { return rep.test(fruit); }

  auto set_head() noexcept { return rep.set(head); }

  auto set_body() noexcept { return rep.set(body); }

  auto set_fruit() noexcept { return rep.set(fruit); }

  auto clear_head() noexcept { return rep.reset(head); }

  auto clear_body() noexcept { return rep.reset(body); }

  auto clear_fruit() noexcept { return rep.reset(fruit); }

  friend bool operator==(cell_info const&, cell_info const&) = default;
};

inline auto with_body(cell_info c) noexcept {
  c.set_body();
  return c;
}

inline auto with_head(cell_info c) noexcept {
  c.set_head();
  return c;
}

inline auto with_fruit(cell_info c) noexcept {
  c.set_fruit();
  return c;
}

inline auto without_body(cell_info c) noexcept {
  c.clear_body();
  return c;
}

inline auto without_head(cell_info c) noexcept {
  c.clear_head();
  return c;
}

inline auto without_fruit(cell_info c) noexcept {
  c.clear_fruit();
  return c;
}
}  // namespace snk
