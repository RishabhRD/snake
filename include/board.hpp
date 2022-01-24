#pragma once

#include <cstddef>
namespace snk {
class board_t {
  std::size_t width_{};
  std::size_t height_{};

public:
  explicit board_t(std::size_t width, std::size_t height)// NOLINT
    : width_(width), height_(height) {}

  [[nodiscard]] std::size_t width() const { return width_; }

  [[nodiscard]] std::size_t height() const { return height_; }
};
}// namespace snk
