#pragma once

#include <cstddef>
namespace snk {
class board_t {
  int width_{};
  int height_{};

public:
  explicit board_t(int width, int height)// NOLINT
    : width_(width), height_(height) {}

  [[nodiscard]] int width() const { return width_; }

  [[nodiscard]] int height() const { return height_; }
};
}// namespace snk
