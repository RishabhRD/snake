#pragma once

#include <variant>
#include "event.hpp"
#include "state.hpp"

namespace snk {
struct event_handler {
  auto operator()(events::direction_change evt, states::running state) const {
    state.next_snake_dir = evt.direction;
    return state;
  }

  auto operator()(events::quit, auto const&) const { return states::quit{}; }

  auto operator()(events::play_pause, states::running state) const {
    return states::paused{std::move(state)};
  }

  auto operator()(events::play_pause, states::paused state) const {
    return std::move(state.running_game);
  }

  // TODO: handle game start
  auto operator()(events::start, auto const&) const { return states::quit{}; }

  auto operator()(events::start, states::quit) const { return states::quit{}; }

  auto operator()(auto, auto state) const { return state; }
};

inline auto process_event(events::event evt, states::state state) {
  return std::visit<states::state>(event_handler{}, evt, std::move(state));
}
}  // namespace snk
