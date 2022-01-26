#include "input_handler.hpp"
#include "rd/overload.hpp"
#include "rd/variant_then.hpp"
#include <variant>

namespace snk {
auto handle_quit(snk::state_t &state) -> void { state = snk::closed_t{}; }

auto handle_dir(snk::running_t &state, snk::direction_input_t input) -> void {
  state.queued_direction_inputs().push_back(input);
}

auto handle_input(snk::input_t input, snk::state_t &state) -> void {
  std::visit(rd::overload{ [&state](snk::direction_input_t dir_input) {
                            rd::then<snk::running_t>(state,
                              [dir_input](snk::running_t &running_state) {
                                handle_dir(running_state, dir_input);
                              });
                          },
               [&state](snk::quit_input_t) { handle_quit(state); } },
    input);
}
}// namespace snk
