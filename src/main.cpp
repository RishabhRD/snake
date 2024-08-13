#include <chrono>
#include <iostream>
#include "init.hpp"
#include "random.hpp"
#include "run.hpp"

auto print_help() {
  std::cout << "       Snake Game\n";
  std::cout << "Start/Restart -> Enter\n";
  std::cout << "UP            -> W, K, <UP>\n";
  std::cout << "DOWN          -> S, J, <DOWN>\n";
  std::cout << "LEFT          -> A, H, <LEFT>\n";
  std::cout << "RIGHT         -> D, L, <RIGHT>\n";
  std::cout << "Play/Pause    -> Space\n";
  std::cout << "Quit          -> Escape\n";
}

int main(int argc, char** argv) {
  using namespace std::literals;
  if (argc >= 2 and (argv[1] == "--help"sv or argv[1] == "-h"sv)) {
    print_help();
  } else {
    auto prop = snk::init_config(argc, argv);
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    snk::random_gen gen(static_cast<unsigned long>(seed));
    snk::run(std::move(prop), gen);
  }
  return 0;
}
