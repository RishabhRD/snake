#pragma once

#include "input.hpp"
#include "tl/optional.hpp"
#include <SFML/Graphics.hpp>

namespace snk {
auto to_input(sf::Event const &event) -> tl::optional<input_t>;
}
