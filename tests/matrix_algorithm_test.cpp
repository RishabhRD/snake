#include "matrix_algorithm.hpp"
#include "doctest.hpp"

test("count") {
  std::vector<std::vector<int>> matrix{{0, 1, 0}, {0, 0, 0}};
  req(nostd::count(matrix, 0) == 5);
}

test("find_n") {
  std::vector<std::vector<int>> matrix{{0, 1, 0}, {0, 0, 0}};
  auto [i, j] = nostd::find_n(matrix, 0, 3);
  req(i == 1);
  req(j == 0);
}

test("find") {
  std::vector<std::vector<int>> matrix{{0, 1, 0}, {0, 0, 0}};
  auto [i, j] = nostd::find(matrix, 0);
  req(i == 0);
  req(j == 0);
}
