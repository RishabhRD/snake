#include <chrono>
#include "init.hpp"
#include "random.hpp"
#include "run.hpp"

int main(int argc, char** argv) {
  auto prop = snk::init_config(argc, argv);
  auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
  snk::random_gen gen(static_cast<unsigned long>(seed));
  snk::run(std::move(prop), gen);
}
