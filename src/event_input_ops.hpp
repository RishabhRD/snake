#pragma once

#include "event.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

namespace snk {
auto to_input(sf::Event const &event) -> std::optional<event::event_t>;
}
