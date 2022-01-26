#pragma once

#include "input.hpp"
#include "state.hpp"

namespace snk {
auto handle_input(snk::input_t input, snk::state_t &state) -> void;
}// namespace snk
