#pragma once

#include <vector>
template<typename T> struct mock_generator {
  explicit mock_generator(std::vector<T> vec) : vec_(vec), cur_(begin(vec)) {}

  auto operator()() {
    auto val = *cur_;
    cur_++;
    return val;
  }

private:
  std::vector<T> vec_;
  typename std::vector<T>::iterator cur_;
};
