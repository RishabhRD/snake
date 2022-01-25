#pragma once

#include "state.hpp"
#include <cstddef>
#include <chrono>
namespace snk {
void try_moving_snake(snk::running_t &state);

void check_collision(snk::state_t &state);

struct try_eating_t {
  void operator()(snk::running_t &state, auto &&fruit_generator) const;
  void operator()(snk::running_t &state) const;
};
inline auto const try_eating = try_eating_t{};
}// namespace snk
