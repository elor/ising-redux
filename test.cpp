#include "catch2/catch_test_macros.hpp"

#include <fmt/format.h>

TEST_CASE("test", "[test]") { REQUIRE(1 == 1); }

TEST_CASE("fmt_test", "[fmt]") {
  REQUIRE(fmt::format("Hello, {}!", "World") == "Hello, World!");
}
