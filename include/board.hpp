#pragma once

#include <cstddef>
#include <compare>
namespace snk {
class board_t {
  int width_{};
  int height_{};

public:
  explicit board_t(int width, int height)// NOLINT
    : width_(width), height_(height) {}

  [[nodiscard]] auto width() const -> int { return width_; }

  [[nodiscard]] auto height() const -> int { return height_; }

  friend auto operator==(const board_t &, const board_t &) -> bool = default;
};
}// namespace snk
