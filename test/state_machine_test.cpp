#include "board.hpp"
#include "event_handler.hpp"
#include "snake.hpp"
#include "state.hpp"
#include "test_include.hpp"

suite const state_machine_suite = [] {
  using namespace std::chrono_literals;
  snk::board_t board{ 10, 10 };
  snk::snake_t old_snake{
    { { 3, 3 }, { 4, 3 } }, snk::direction_t::east, board
  };
  "straight move"_test = [=] {
    auto const cur_time = std::chrono::system_clock::now();
    snk::running_t running_state{ old_snake, { 5, 5 }, 6, cur_time };
    auto new_time = cur_time + 1s;
    auto state = snk::handle_event(
      std::move(running_state), snk::event::timeout{ new_time });
    snk::snake_t expected_snake{
      { { 4, 3 }, { 5, 3 } }, snk::direction_t::east, board
    };
    snk::state_t expected_state =
      snk::running_t{ expected_snake, { 5, 5 }, 6, new_time };
    expect(state == expected_state);
  };

  // TODO: Think how to test random fruit generated
};
