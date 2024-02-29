#pragma once

#include <fmt/format.h>
#include <fstream>
#include <vector>

#include <ising.hpp>

struct Run_Result {
  std::vector<double> times;
  std::vector<double> energies;
  std::vector<double> magnetizations;
  std::vector<int> up_spins;
  std::vector<int> down_spins;

  void write_csv(std::string filename) const {
    std::ofstream file(filename);

    // csv header
    file << "time,energy,magnetization,up_spins,down_spins\n";

    // csv data
    for (int i = 0; i < times.size(); ++i) {
      file << fmt::format("{},{},{},{},{}\n", times[i], energies[i],
                          magnetizations[i], up_spins[i], down_spins[i]);
    }
  }
};

struct Single_Result {
  double time;
  double energy;
  double magnetization;
  int up_spins;
  int down_spins;
};

template <int N> Run_Result run_ising(Ising<N> &ising, int num_flips) {
  Run_Result result;

  ising.init_randomly();
  ising.init_checkerboard();

  double time{0.0};

  auto store_result = [&result, &ising](double time) {
    result.times.push_back(time);
    result.energies.push_back(ising.getE());
    result.magnetizations.push_back(ising.getM());
    auto [up, down] = ising.getSpins();
    result.up_spins.push_back(up);
    result.down_spins.push_back(down);
  };

  double old_E = ising.getE();

  result.times.reserve(num_flips);
  result.energies.reserve(num_flips);
  result.magnetizations.reserve(num_flips);
  result.up_spins.reserve(num_flips);
  result.down_spins.reserve(num_flips);

  auto rng = std::mt19937{std::random_device{}()};
  auto idist = std::uniform_int_distribution<int>{0, N - 1};
  auto ddist = std::uniform_real_distribution<double>{0.0, 1.0};
  for (int flips = 0; flips < num_flips; ++flips) {
    store_result(flips);

    int i = idist(rng);
    int j = idist(rng);

    double probability = ising.flip_probability(i, j);

    if (ddist(rng) < probability) {
      ising.flip(i, j);
    }
  }

  store_result(num_flips);

  return result;
}

template <int N>
Single_Result run_ising_nostore(Ising<N> &ising, int num_flips) {
  ising.init_randomly();
  ising.init_checkerboard();

  double time{0.0};

  auto rng = std::mt19937{std::random_device{}()};
  auto idist = std::uniform_int_distribution<int>{0, N - 1};
  auto ddist = std::uniform_real_distribution<double>{0.0, 1.0};
  for (int flips = 0; flips < num_flips; ++flips) {
    int i = idist(rng);
    int j = idist(rng);

    double probability = ising.flip_probability(i, j);

    if (ddist(rng) < probability) {
      ising.flip(i, j);
    }
  }

  auto [up_spins, down_spins] = ising.getSpins();

  return {
      .time = time,
      .energy = ising.getE(),
      .magnetization = ising.getM(),
      .up_spins = up_spins,
      .down_spins = down_spins,
  };
}
