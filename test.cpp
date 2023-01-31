#include "catch2/catch_test_macros.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

#include<fmt/format.h>

TEST_CASE("test", "[test]") {
    REQUIRE(1 == 1);
}

TEST_CASE("fmt_test", "[fmt]") {
    REQUIRE(fmt::format("Hello, {}!", "World") == "Hello, World!");
}

