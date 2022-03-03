#pragma once

#include "state.hpp"
#include "point.hpp"

namespace snk {
auto random_fruit_for(snk::fruit_needed_t const &state) -> snk::point_t;
}// namespace snk
