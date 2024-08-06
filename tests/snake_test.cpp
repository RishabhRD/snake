#include "doctest.hpp"
#include "snake.hpp"
#include <algorithm>
#include <vector>

using namespace snk;

test("initializing snake should give correct body and head") {
  snake s{ point{ 0, 0 } };
  req(s.head() == point{ 0, 0 });
  req(std::ranges::equal(s.body(), std::vector{ point{ 0, 0 } }));
}

test("grow should add head correctly") {
  snake s{ point{ 0, 0 } };
  s.grow(direction::right);
  req(
    std::ranges::equal(s.body(), std::vector{ point{ 0, 0 }, point{ 1, 0 } }));
}
