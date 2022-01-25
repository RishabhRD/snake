#pragma once

#include "state.hpp"
#include <cstddef>
#include <chrono>
namespace snk {
void try_moving_snake(snk::running_t &state);
void try_eating(snk::running_t &state);
void check_collision(snk::state_t &state);
}// namespace snk
