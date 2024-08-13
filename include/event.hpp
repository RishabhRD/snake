#pragma once
#include <variant>
#include "direction.hpp"

namespace snk::events {
struct direction_change {
  snk::direction direction;

  friend constexpr bool operator==(direction_change const&,
                                   direction_change const&);
};

struct quit {
  friend constexpr bool operator==(quit const&, quit const&);
};

struct play_pause {
  friend constexpr bool operator==(play_pause const&, play_pause const&);
};

struct start {
  friend constexpr bool operator==(start const&, start const&);
};

using event = std::variant<direction_change, quit, play_pause, start>;
}  // namespace snk::events
