#pragma once

#include "property.hpp"
#include "state.hpp"
#include "ui/window.hpp"

namespace snk {
template <ui::Window window_t>
void render(window_t&, states::state const&, ui_properties const&) {
  // TODO: implement rendering
}
}  // namespace snk
