#pragma once

#include "input.hpp"
#include "state.hpp"

namespace snk {
auto handle_quit(snk::state_t &state) -> void;
auto handle_dir(snk::running_t &state, snk::input_t input) -> void;
auto handle_input(snk::input_t input, snk::state_t &state) -> void;
}// namespace snk
