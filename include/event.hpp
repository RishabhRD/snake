#pragma once
#include <variant>
#include "direction.hpp"

namespace snk::events {
struct direction_change {
  snk::direction direction;
};

struct quit {};

struct play_pause {};

struct start {};

using event = std::variant<direction_change, quit, play_pause, start>;
}  // namespace snk::events
