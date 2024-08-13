#pragma once

#include "property.hpp"
#include "state.hpp"
#include "ui/window.hpp"

namespace snk {

struct ui_renderer {
  ui_properties ui_prop;
};

template <ui::Window window_t>
void render(ui_renderer const&, states::state const&, window_t&) {
  // TODO: implement rendering
}
}  // namespace snk
