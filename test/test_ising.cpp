#include "catch2/catch_test_macros.hpp"
#include <catch2/catch_approx.hpp>

#include <fmt/format.h>
#include <iostream>

#include "ising.hpp"
#include "run_ising.hpp"

using Catch::Approx;

TEST_CASE("test", "[test]") { REQUIRE(1 == 1); }

TEST_CASE("ising_test", "[ising]") {
  double H = 0.0;
  double J = 1.0;
  double T = 1.0;
  constexpr int N = 10;

  Ising<N> ising(T, H, J);

  REQUIRE(ising.getM() == N * N);
  REQUIRE(ising.getE() == -4 * N * N);

  ising.setH(1.0);
  REQUIRE(ising.getE() == -5 * N * N);

  ising.flip(0, 0);

  REQUIRE(ising.getM() == N * N - 2);
  REQUIRE(ising.getE() == -5 * N * N + 18);

  REQUIRE(ising.getTcrit() == Approx(2.269185314213022));

  for (int neighbor_sum : {-4, -2, 0, 2, 4}) {
    double probability = ising.flip_probability(0, 0);
    REQUIRE(probability >= 0.0);
    REQUIRE(probability <= 1.0);
  }
}

TEST_CASE("ising_test_rng", "[ising]") {
  constexpr int N = 10;

  double H = 0.0;
  double J = 1.0;
  double T = 1.0;

  Ising<N> ising(T, H, J);

  ising.init_randomly();

  REQUIRE(ising.getM() != 1.0);
  REQUIRE(ising.getM() != -1.0);

  REQUIRE(ising.getE() == Approx(0.0).margin(0.5 * N * N));
}

TEST_CASE("ising_flips", "[ising]") {
  Ising<10> ising(1.0, 0.0, 1.0);
  ising.init_randomly();
  auto result = run_ising(ising, 100);

  double old_E = result.energies.front();
  double new_E = result.energies.back();

  REQUIRE(old_E > new_E);
}
