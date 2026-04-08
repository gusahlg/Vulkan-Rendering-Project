#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "../vk_lib/app.hpp"

int main() {
  try {
    ve::FirstApp app{};
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
