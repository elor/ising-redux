#include <iostream>

#include <run_ising.hpp>

int main(int argc, char **argv) {
  std::cout << "starting" << std::endl;

  constexpr int N = 20;
  constexpr int num_spins = N * N * 10'000;

  double T = 2 * Tcrit();

  Ising<N> ising(T);
  ising.init_randomly();

  auto result = run_ising(ising, num_spins);
  result.write_csv("result.csv");
  ising.write_spins_csv("spins.csv");

  std::cout << "done" << std::endl;
  return 0;
}
