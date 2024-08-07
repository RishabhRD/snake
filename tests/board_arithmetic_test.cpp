#include "board.hpp"
#include "direction.hpp"
#include "doctest.hpp"
#include "board_arithmetic.hpp"


test("returns correct board fill matrix") {
  snk::snake<snk::mod_int> snake{ { { 0, 2 }, { 0, 3 } } };
  snake.grow(snk::direction::right);
  snk::board board{ 2, 3, std::move(snake), { { 1, 2 }, { 1, 3 } } };
  auto matrix = snk::create_board_position_info_matrix(board);
  auto s = snk::board_pos_info::snake;
  auto e = snk::board_pos_info::empty;
  auto f = snk::board_pos_info::fruit;
  std::vector<std::vector<snk::board_pos_info>> expected{
    { s, s }, { e, f }, { e, e }
  };
  req(matrix == expected);
}
