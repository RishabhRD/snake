#include "state_ops.hpp"
#include "input_handler.hpp"
#include "rd/overload.hpp"
#include "rd/variant_then.hpp"
#include <variant>

namespace snk {
auto handle_input(snk::input_t input, snk::state_t &state) -> void {
  std::visit(
    rd::overload{
      [&state](snk::direction_input_t dir_input) {
        rd::then<snk::running_t>(
          state, [dir_input](snk::running_t &running_state) {
            snk::enqueue_direction_input(running_state, dir_input);
          });
      },
      [&state](snk::quit_input_t) { snk::quit_game(state); },
      [&state](snk::play_pause_input_t) { snk::conditional_play_pause(state); },
      [&state](snk::start_input_t) { snk::start_game(state); },
    },
    input);
}
}// namespace snk
