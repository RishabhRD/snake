#include "input_handler.hpp"
#include "rd/variant_then.hpp"

namespace snk {
auto handle_quit(snk::state_t &state) -> void { state = snk::closed_t{}; }

auto handle_dir(snk::running_t &state, snk::input_t input) -> void {
  state.snake().set_cur_direction(*snk::to_direction(input));
}

auto handle_input(snk::input_t input, snk::state_t &state) -> void {
  switch (input) {
  case snk::input_t::quit:
    handle_quit(state);
    break;
  case snk::input_t::down:
  case snk::input_t::up:
  case snk::input_t::right:
  case snk::input_t::left:
    rd::then<snk::running_t>(
      state, [input](snk::running_t &st) { handle_dir(st, input); });
    break;
  }
}
}// namespace snk
