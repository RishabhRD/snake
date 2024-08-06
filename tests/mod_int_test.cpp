#include "mod_int.hpp"
#include "doctest.hpp"

using namespace snk;

test("have correct modulus") {
  mod_int m{ 0, 2 };
  req(m.modulus() == 2);
}

test("have correct value for < 0") {
  req(mod_int{-1, 2} == mod_int{1, 2});
}

test("addition without wrappping") {
  mod_int a{ 0, 2 };
  mod_int b{ 1, 2 };
  auto c = a + b;
  req(c == mod_int{ 1, 2 });
  req(c.modulus() == 2);
}

test("addition with wrappping") {
  mod_int a{ 1, 2 };
  mod_int b{ 1, 2 };
  auto c = a + b;
  req(c == mod_int{ 0, 2 });
  req(c.modulus() == 2);
}

test("substraction without wrappping") {
  mod_int a{ 1, 2 };
  mod_int b{ 1, 2 };
  auto c = a - b;
  req(c == mod_int{ 0, 2 });
  req(c.modulus() == 2);
}

test("substraction with wrappping") {
  mod_int a{ 0, 2 };
  mod_int b{ 1, 2 };
  auto c = a - b;
  req(c == mod_int{ 1, 2 });
  req(c.modulus() == 2);
}

test("pre increment without wrapping") {
  mod_int a{ 0, 2 };
  auto const &x = ++a;
  req(&a == &x);
  req(a == mod_int{ 1, 2 });
}

test("pre increment with wrapping") {
  mod_int a{ 1, 2 };
  auto const &x = ++a;
  req(&a == &x);
  req(a == mod_int{ 0, 2 });
}

test("pre decrement without wrapping") {
  mod_int a{ 1, 2 };
  auto const &x = --a;
  req(&a == &x);
  req(a == mod_int{ 0, 2 });
}

test("pre decrement with wrapping") {
  mod_int a{ 0, 2 };
  auto const &x = --a;
  req(&a == &x);
  req(a == mod_int{ 1, 2 });
}

test("post increment without wrapping") {
  mod_int a{ 0, 2 };
  auto x = a++;
  req(a == mod_int{ 1, 2 });
  req(x == mod_int{ 0, 2 });
  req(x.modulus() == 2);
}

test("post increment with wrapping") {
  mod_int a{ 1, 2 };
  auto x = a++;
  req(a == mod_int{ 0, 2 });
  req(x == mod_int{ 1, 2 });
  req(x.modulus() == 2);
}

test("post decrement without wrapping") {
  mod_int a{ 1, 2 };
  auto x = a--;
  req(a == mod_int{ 0, 2 });
  req(x == mod_int{ 1, 2 });
  req(x.modulus() == 2);
}

test("post decrement with wrapping") {
  mod_int a{ 0, 2 };
  auto x = a--;
  req(a == mod_int{ 1, 2 });
  req(x == mod_int{ 0, 2 });
  req(x.modulus() == 2);
}
