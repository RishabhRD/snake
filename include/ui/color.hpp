#pragma once

namespace snk {
struct color {
  unsigned int r;
  unsigned int g;
  unsigned int b;

  friend bool operator==(color const&, color const&) = default;
};
}  // namespace snk
