#pragma once

#include <chrono>
#include "event_handler.hpp"
#include "state.hpp"
#include "state_arithmetic.hpp"
#include "ui/render.hpp"
#include "ui/window.hpp"

namespace snk::gameloop {
template <ui::Window window_t, typename Random>
void run(states::state state, window_t& win, event_handler const& handler,
         Random&& rand) {
  auto prev_time = std::chrono::steady_clock::now();
  std::chrono::milliseconds const tick_threshold{32};  // 30 ticks per second
  std::chrono::milliseconds accumulated_time{0};
  while (state != states::state{states::quit{}}) {
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        current_time - prev_time);
    prev_time = current_time;
    accumulated_time += elapsed_time;

    state = process_events(handler, win.poll_events(), std::move(state));

    while (accumulated_time >= tick_threshold) {
      state = after_time(tick_threshold, std::move(state), rand);
      accumulated_time -= tick_threshold;
      render(win, state);
    }
  }
}
}  // namespace snk::gameloop
