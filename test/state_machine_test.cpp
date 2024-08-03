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

  "collision"_test = [board] {
    auto const cur_time = std::chrono::system_clock::now();
    snk::snake_t given_snake{
      { { 4, 3 }, { 5, 3 }, { 6, 3 }, { 6, 2 }, { 5, 2 } },
      snk::direction_t::west,
      board
    };
    snk::state_t cur_state =
      snk::running_t{ given_snake, { 5, 5 }, 6, cur_time };
    cur_state = snk::handle_event(
      std::move(cur_state), snk::event::direction_change::down);
    auto new_time = cur_time + 1s;
    cur_state =
      snk::handle_event(std::move(cur_state), snk::event::timeout{ new_time });
    cur_state =
      snk::handle_event(std::move(cur_state), snk::event::timeout{ new_time });
    snk::state_t expected_state{ snk::finished_t{ 5 } };
    expect(cur_state == expected_state);
  };

  "eating straight"_test = [=] {
    auto const cur_time = std::chrono::system_clock::now();
    snk::running_t running_state{ old_snake, { 4, 3 }, 6, cur_time };
    auto new_time = cur_time + 1s;
    auto state = snk::handle_event(
      std::move(running_state), snk::event::timeout{ new_time });
    snk::snake_t expected_snake{
      { { 3, 3 }, { 4, 3 }, { 5, 3 } }, snk::direction_t::east, board
    };
    snk::state_t expected_state = snk::fruit_needed_t{ snk::running_t{
      expected_snake, { 4, 3 }, 6, new_time } };
    expect(eq(std::get<snk::fruit_needed_t>(state).snake(), expected_snake));
    expect(state == expected_state);
    state = snk::handle_event(
      std::move(state), snk::event::fruit_generated{ { 7, 3 } });
    expected_state = snk::running_t{ expected_snake, { 7, 3 }, 6, new_time };
    expect(state == expected_state);
  };

  "eating with direction"_test = [=] {
    auto const cur_time = std::chrono::system_clock::now();
    snk::state_t state = snk::running_t{ old_snake, { 4, 3 }, 6, cur_time };
    auto new_time = cur_time + 1s;
    state =
      snk::handle_event(std::move(state), snk::event::direction_change::up);
    state =
      snk::handle_event(std::move(state), snk::event::timeout{ new_time });
    snk::snake_t expected_snake{
      { { 3, 3 }, { 4, 3 }, { 4, 2 } }, snk::direction_t::north, board
    };
    snk::state_t expected_state = snk::fruit_needed_t{ snk::running_t{
      expected_snake, { 4, 3 }, 6, new_time } };
    expect(eq(std::get<snk::fruit_needed_t>(state).snake(), expected_snake));
    expect(state == expected_state);
    state = snk::handle_event(
      std::move(state), snk::event::fruit_generated{ { 7, 3 } });
    expected_state = snk::running_t{ expected_snake, { 7, 3 }, 6, new_time };
    expect(state == expected_state);
  };

  "eating on snake edge"_test = [board] {
    auto const cur_time = std::chrono::system_clock::now();
    snk::snake_t given_snake{ { { 3, 3 },
                                { 4, 3 },
                                { 5, 3 },
                                { 6, 3 },
                                { 7, 3 },
                                { 7, 2 },
                                { 7, 1 },
                                { 6, 1 },
                                { 6, 2 } },
      snk::direction_t::south,
      board };
    snk::state_t state = snk::running_t{ given_snake, { 6, 2 }, 6, cur_time };
    auto new_time = cur_time + 1s;
    state =
      snk::handle_event(std::move(state), snk::event::direction_change::left);
    state =
      snk::handle_event(std::move(state), snk::event::timeout{ new_time });
    snk::snake_t expected_snake{ { { 3, 3 },
                                   { 4, 3 },
                                   { 5, 3 },
                                   { 6, 3 },
                                   { 7, 3 },
                                   { 7, 2 },
                                   { 7, 1 },
                                   { 6, 1 },
                                   { 6, 2 },
                                   { 5, 2 } },
      snk::direction_t::west,
      board };
    expect(eq(std::get<snk::fruit_needed_t>(state).snake(), expected_snake));
    snk::state_t expected_state = snk::fruit_needed_t{ snk::running_t{
      expected_snake, { 6, 2 }, 6, new_time } };
    expect(state == expected_state);
    state = snk::handle_event(
      std::move(state), snk::event::fruit_generated{ { 9, 9 } });
    expected_state = snk::running_t{ expected_snake, { 9, 9 }, 6, new_time };
    expect(state == expected_state);
  };
};
