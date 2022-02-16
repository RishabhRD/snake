#pragma once

#include "event.hpp"
#include "state.hpp"

namespace snk {
auto handle_input(snk::event::event_t input, snk::state_t &state) -> void;
}// namespace snk
