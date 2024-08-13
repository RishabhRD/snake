#include "board.hpp"
#include "doctest.hpp"

using namespace snk;

test("cell info default construction") {
  cell_info c{};
  req(c.is_empty());
  req_false(c.has_body());
  req_false(c.has_head());
  req_false(c.has_fruit());
}

test("cell info fruit op") {
  cell_info c{};
  c.set_fruit();
  req_false(c.is_empty());
  req(c.has_fruit());
  req_false(c.has_body());
  req_false(c.has_head());

  c.clear_fruit();
  req(c.is_empty());
  req_false(c.has_fruit());
  req_false(c.has_body());
  req_false(c.has_head());
}

test("cell info body op") {
  cell_info c{};
  c.set_body();
  req_false(c.is_empty());
  req_false(c.has_fruit());
  req(c.has_body());
  req_false(c.has_head());

  c.clear_body();
  req(c.is_empty());
  req_false(c.has_fruit());
  req_false(c.has_body());
  req_false(c.has_head());
}

test("cell info head op") {
  cell_info c{};
  c.set_head();
  req_false(c.is_empty());
  req_false(c.has_fruit());
  req(c.has_head());
  req_false(c.has_body());

  c.clear_head();
  req(c.is_empty());
  req_false(c.has_fruit());
  req_false(c.has_body());
  req_false(c.has_head());
}

test("cell info multiple op") {
  cell_info c{};
  c.set_body();
  c.set_fruit();
  req_false(c.is_empty());
  req(c.has_fruit());
  req_false(c.has_head());
  req(c.has_body());

  c.clear_body();
  req_false(c.is_empty());
  req(c.has_fruit());
  req_false(c.has_head());
  req_false(c.has_body());
}
