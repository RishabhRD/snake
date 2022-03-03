#include "event_handler.hpp"
#include "rd/overload.hpp"
#include "rd/variant_then.hpp"
#include "rd/vector_util.hpp"
#include "init_game_data.hpp"
#include "running_state_ops.hpp"
#include "state.hpp"
#include <boost/hof/flow.hpp>
#include <utility>
#include <variant>

namespace snk {
class event_handler_visitor {
  state_t state;

public:
  explicit event_handler_visitor(state_t state_p) : state(std::move(state_p)) {}

  auto operator()(event::quit /*unused*/) const { return closed_t{}; }

  auto operator()(event::start /*unused*/) {
    constexpr static std::size_t speed = 10;
    constexpr static snk::point_t init_fruit_position = { 17, 10 };

    if (!rd::is<snk::closed_t>(state)) {
      snk::board_t board{ snk::game_data::num_tiles_x,
        snk::game_data::num_tiles_y };
      snk::snake_t init_snake{
        { { 9, 10 }, { 10, 10 }, { 11, 10 } }, snk::direction_t::east, board
      };
      state = snk::running_t{ std::move(init_snake),
        init_fruit_position,
        speed,
        std::chrono::system_clock::now() };
    }
    return std::move(state);
  }

  auto operator()(event::play_pause /*unused*/) {
    if (rd::is<snk::running_t>(state)) {
      state = snk::paused_t{ std::move(std::get<snk::running_t>(state)) };
    } else if (rd::is<snk::paused_t>(state)) {
      state = std::move(std::get<snk::paused_t>(state)).running_state();
    }
    return std::move(state);
  }

  auto operator()(event::direction_change dir) {
    if (rd::is<running_t>(state)) {
      auto &running_state = std::get<running_t>(state);
      running_state = queue_direction(std::move(running_state), dir);
    }
    return std::move(state);
  }

  auto operator()(event::timeout timeout) -> state_t {
    return std::move(state)
           | rd::then<running_t>([timeout](snk::running_t running_state) {
               return std::move(running_state).with_last_tick(timeout.cur_time);
             })
           | rd::then<running_t>(check_collision)
           | rd::then<running_t>(
             boost::hof::flow(snk::apply_queued_directions, snk::try_eating))
           | rd::then<running_t>(move_snake);
  }

  auto operator()(event::fruit_generated fruit) -> state_t {
    if (rd::is<fruit_needed_t>(state)) {
      return std::get<fruit_needed_t>(std::move(state))
        .provide_fruit(fruit.fruit_pos);
    }
    return std::move(state);
  }
};

auto handle_event(state_t state, event::event_t event) -> state_t {
  return std::visit<snk::state_t>(
    event_handler_visitor{ std::move(state) }, event);
}
}// namespace snk
