#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <random>
#include <ranges>
#include <tuple>

#include <fmt/format.h>

using Spin = int;

constexpr Spin UP{1};
constexpr Spin DOWN{-1};
constexpr double kB{1.0};

inline double Tcrit(double J = 1.0) { return J * 2.269185314213022; }

template <int N> class Ising {
public:
  Ising(double T = Tcrit(1.0), double H = 0.0, double J = 1.0)
      : T(T), H(H), J(J) {
    init_all_up();
  }

  void init_all_up() {
    for (auto &row : spins) {
      row.fill(UP);
    }
  }

  void init_randomly() {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 1);

    for (auto &row : spins) {
      for (auto &spin : row) {
        spin = uniform_dist(e1) * 2 - 1;
      }
    }

    for (auto &row : spins) {
      for (auto &spin : row) {
        assert(spin == UP || spin == DOWN);
      }
    }
  }

  void init_checkerboard() {
    bool is_white = true;

    for (auto &row : spins) {
      for (auto &spin : row) {
        spin = is_white ? UP : DOWN;
        is_white = !is_white;
      }
      is_white = !is_white;
    }
  }

  double getM() const {
    int M = 0.0;

    for (const auto &row : spins) {
      for (const auto &spin : row) {
        M += spin;
      }
    }

    return static_cast<double>(M);
  }

  int neighbor_sum(int i, int j) const {
    int neighbor_sum = 0;

    // neighbor left
    int n_i = (i - 1 + N) % N;
    neighbor_sum += spins[n_i][j];

    // neighbor right
    n_i = (i + 1) % N;
    neighbor_sum += spins[n_i][j];

    // neighbor above
    int n_j = (j - 1 + N) % N;
    neighbor_sum += spins[i][n_j];

    // neighbor below
    n_j = (j + 1) % N;
    neighbor_sum += spins[i][n_j];

    return neighbor_sum;
  }

  double getE() const {
    double E = 0.0;

    // sum up all influences of the external field H
    for (const auto &row : spins) {
      for (const auto &spin : row) {
        E += -H * spin;
      }
    }

    // sum up all influences of the interaction J
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        E += -J * spins[i][j] * neighbor_sum(i, j);
      }
    }

    return E;
  }

  double getTcrit() const { return Tcrit(J); }

  void setH(double H) { this->H = H; }
  void setT(double T) { this->T = T; }

  int flip(int i, int j) { return spins[i][j] *= -1; }

  double delta_E(int i, int j) const {
    const int neighbor_sum = this->neighbor_sum(i, j);
    const int spin_before = spins[i][j];
    const int spin_after = -spin_before;

    double E = 0.0;

    E -= -H * spin_before;
    E += -H * spin_after;

    E -= 2 * -J * spin_before * neighbor_sum;
    E += 2 * -J * spin_after * neighbor_sum;

    return E;
  }

  constexpr double flip_probability_time_evolution(int i, int j) const {
    const double delta_E = this->delta_E(i, j);

    const double x = std::exp(-delta_E / (kB * T));

    return x / (1.0 + x);
  }

  constexpr double flip_probability_equilibrium(int i, int j) const {
    const double delta_E = this->delta_E(i, j);

    const double P = std::exp(-delta_E / (kB * T));

    return std::min(1.0, P);
  }

  constexpr double flip_probability(int i, int j) const {
    return flip_probability_equilibrium(i, j);
  }

  std::tuple<int, int> getSpins() const {
    int up_spins = 0;
    int down_spins = 0;

    for (const auto &row : this->spins) {
      for (const auto &spin : row) {
        up_spins += spin == UP;
        down_spins += spin == DOWN;
      }
    }

    return {up_spins, down_spins};
  }

  void write_spins_csv(std::string filename) {
    std::ofstream file(filename);

    // csv header: x,y,spin
    file << "x,y,spin\n";

    // all spins and their x/y pos
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; j++) {
        file << fmt::format("{},{},{}\n", i, j, spins[i][j]);
      }
    }
  }

private:
  double T;
  double H;
  const double J;

  std::array<std::array<Spin, N>, N> spins;
};
