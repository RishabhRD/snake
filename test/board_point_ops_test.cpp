#include "board.hpp"
#include "board_point_ops.hpp"
#include "point.hpp"
#include "test_include.hpp"

suite const board_point_ops = [] {
  "point in board"_test = [] {
    snk::point_t const actual_point{ 52, 68 };
    snk::point_t const expected_point{ 2, 8 };
    snk::board_t const board{ 10, 10 };
    expect(eq(snk::in_board(actual_point, board), expected_point));
  };
};
