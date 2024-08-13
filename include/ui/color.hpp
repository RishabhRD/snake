#pragma once

namespace snk::ui {
struct color {
  unsigned char r;
  unsigned char g;
  unsigned char b;

  friend bool operator==(color const&, color const&) = default;
};
}  // namespace snk::ui
