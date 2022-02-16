#pragma once

#include "event.hpp"
#include "state.hpp"

namespace snk {
auto handle_event(snk::state_t state, snk::event::event_t event)
  -> snk::state_t;
}// namespace snk
