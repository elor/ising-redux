#include <iostream>
#include <fmt/format.h>

int main(int argc, char **argv) {
  std::cout << fmt::format("Hello, {}!", "World") << std::endl;

  return 0;
}
