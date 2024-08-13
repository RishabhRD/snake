#include "board_arithmetic.hpp"
#include "board.hpp"
#include "direction.hpp"
#include "doctest.hpp"

namespace board_arithmetic_test {
auto e = snk::cell_info{};
auto b = snk::with_body(e);
auto h = snk::with_head(e);
auto f = snk::with_fruit(e);
}  // namespace board_arithmetic_test

using namespace board_arithmetic_test;

test("returns correct board fill matrix") {
  snk::snake<snk::mod_int> snake{{{0, 2}, {0, 3}}};
  snake.grow(snk::direction::right);
  snake.grow(snk::direction::down);
  snk::board board{2, 3, std::move(snake), {1, 1}};
  auto matrix = snk::create_board_matrix(board);
  std::vector<std::vector<snk::cell_info>> expected{
      {b, b}, {e, snk::with_head(f)}, {e, e}};
  req(matrix == expected);
}

test("select empty cell") {
  std::vector<std::vector<snk::cell_info>> matrix{{b, h}, {e, f}, {e, f}};
  auto pnt = snk::select_empty_cell(matrix, [](auto, auto n) { return n; });
  req(pnt.x == 0);
  req(pnt.y == 2);
}

test("select empty cell with no empty cell") {
  std::vector<std::vector<snk::cell_info>> matrix{{b, h}, {b, b}, {b, b}};
  auto pnt = snk::select_empty_cell(matrix, [](auto, auto n) { return n; });
  req(pnt.x == 2);
  req(pnt.y == 3);
}
