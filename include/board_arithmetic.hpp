#pragma once

#include "board.hpp"
#include "mod_int.hpp"
#include "point.hpp"
#include "snake.hpp"

namespace snk {
namespace __details {
  inline auto fill_snake_matrix(
    std::vector<std::vector<board_pos_info>> &matrix,
    snake<mod_int> const &snake) {
    for (auto const &point : snake.body()) {
      auto const x = static_cast<std::size_t>(point.x.value());
      auto const y = static_cast<std::size_t>(point.y.value());
      matrix[y][x] = board_pos_info::snake;
    }
  }

  inline auto fill_fruit_matrix(
    std::vector<std::vector<board_pos_info>> &matrix,
    point<mod_int> const &fruit) {
    auto fruit_x = static_cast<std::size_t>(fruit.x.value());
    auto fruit_y = static_cast<std::size_t>(fruit.y.value());
    matrix[fruit_y][fruit_x] = board_pos_info::fruit;
  }
}// namespace __details

// Precondition:
//   - board.snake.head().x.modulus() == width
//   - board.snake.head().y.modulus() == height
//   - board.fruit_pos.x.modulus() == width
//   - board.fruit_pos.y.modulus() == height
// Postcondition:
//   - Returns a matrix with #rows = board.height, #cols = board.width
//   - if matrix[y][x] represents board at position (x, y) is occupied with
//     matrix[y][x] value
inline auto create_board_position_info_matrix(snk::board const &b) {
  std::vector matrix(b.height, std::vector(b.width, board_pos_info::empty));
  __details::fill_snake_matrix(matrix, b.snake);
  __details::fill_fruit_matrix(matrix, b.fruit_pos);
  return matrix;
}
}// namespace snk
