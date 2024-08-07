#include "board_arithmetic.hpp"
#include "board.hpp"
#include "direction.hpp"
#include "doctest.hpp"

namespace board_arithmetic_test {
constexpr auto s = snk::board_pos_info::snake_body;
constexpr auto sh = snk::board_pos_info::snake_head;
constexpr auto e = snk::board_pos_info::empty;
constexpr auto f = snk::board_pos_info::fruit;
}  // namespace board_arithmetic_test

using namespace board_arithmetic_test;

test("returns correct board fill matrix") {
  snk::snake<snk::mod_int> snake{{{0, 2}, {0, 3}}};
  snake.grow(snk::direction::right);
  snk::board board{2, 3, std::move(snake), {1, 1}};
  auto matrix = snk::create_board_matrix(board);
  std::vector<std::vector<snk::board_pos_info>> expected{
      {s, sh}, {e, f}, {e, e}};
  req(matrix == expected);
}

test("select empty cell") {
  std::vector<std::vector<snk::board_pos_info>> matrix{{s, sh}, {e, f}, {e, f}};
  auto pnt = snk::select_empty_cell(matrix, [](auto, auto n) { return n; });
  req(pnt.x == 0);
  req(pnt.y == 2);
}

test("select empty cell with no empty cell") {
  std::vector<std::vector<snk::board_pos_info>> matrix{{s, sh}, {s, s}, {s, s}};
  auto pnt = snk::select_empty_cell(matrix, [](auto, auto n) { return n; });
  req(pnt.x == 2);
  req(pnt.y == 3);
}
