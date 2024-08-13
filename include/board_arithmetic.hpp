#pragma once

#include "board.hpp"
#include "matrix_algorithm.hpp"
#include "mod_int.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "snake_arithmetic.hpp"

namespace snk {
namespace __details {
inline auto fill_snake_matrix(std::vector<std::vector<cell_info>>& matrix,
                              snake<mod_int> const& snake) {
  for (auto const& point : snake.body()) {
    auto const x = static_cast<std::size_t>(point.x.value());
    auto const y = static_cast<std::size_t>(point.y.value());
    matrix[y][x].set_body();
  }
  auto const head_x = static_cast<std::size_t>(snake.head().x.value());
  auto const head_y = static_cast<std::size_t>(snake.head().y.value());
  matrix[head_y][head_x].clear_body();
  matrix[head_y][head_x].set_head();
}

inline auto fill_fruit_matrix(std::vector<std::vector<cell_info>>& matrix,
                              point<std::size_t> const& fruit) {
  matrix[fruit.y][fruit.x].set_fruit();
}
}  // namespace __details

// Precondition:
//   - board.snake.head().x.modulus() == width
//   - board.snake.head().y.modulus() == height
//   - board.fruit_pos.x < width
//   - board.fruit_pos.y < height
// Postcondition:
//   - Returns a matrix with #rows = board.height, #cols = board.width
//   - if matrix[y][x] represents board at position (x, y) is occupied with
//     matrix[y][x] value
inline auto create_board_matrix(snk::board const& b) {
  std::vector matrix(b.height, std::vector(b.width, cell_info{}));
  __details::fill_snake_matrix(matrix, b.snake);
  __details::fill_fruit_matrix(matrix, b.fruit_pos);
  return matrix;
}

// Precondition:
//   - matrix[y][x] represents the board position info at position (x, y)
// Postcondition:
//   - returns a point (x, y) that is empty cell
//   - in case of no empty point is found (width, height) is returned
template <typename RandomGenerator>
inline auto select_empty_cell(std::vector<std::vector<cell_info>> const& matrix,
                              RandomGenerator&& generator) {
  auto const empty_cnt = nostd::count(matrix, cell_info{});
  if (empty_cnt == 0)
    return point{matrix[0].size(), matrix.size()};
  auto const nth = generator(1, empty_cnt);
  auto const cell = nostd::find_n(matrix, cell_info{}, nth);
  return point{cell.second, cell.first};
}

// Postcondition:
//   - returns is_collided_to_self(board.snake)
inline auto has_collision(snk::board const& board) {
  return is_collided_to_self(board.snake);
}
}  // namespace snk
