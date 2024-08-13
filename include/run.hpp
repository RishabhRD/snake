#pragma once

#include "event_handler.hpp"
#include "game_loop.hpp"
#include "property.hpp"
#include "state.hpp"
#include "ui/sfml.hpp"
#include "ui/window.hpp"

namespace snk {

template <ui::Window window_t, typename Random>
void run(app_properties prop, window_t& win, Random&& rand) {
  states::state state{states::init{}};
  event_handler evt_handler{std::move(prop.game_properties)};
  gameloop::run(state, win, evt_handler, prop.ui_properties, rand);
}

template <typename Random>
void run(app_properties prop, Random&& rand) {
  ui::Window auto win = ui::make_window(prop);
  run(std::move(prop), win, rand);
}
}  // namespace snk
