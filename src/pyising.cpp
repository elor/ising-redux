#include <pybind11/pybind11.h>
#include <tuple>

#include <run_ising.hpp>

Single_Result run(double T, double H, int steps) {
  Ising<20> ising(T, H);
  ising.init_randomly();

  return run_ising_nostore(ising, steps);
}

namespace py = pybind11;

PYBIND11_MODULE(pyising, m) {
  m.def("run", &run,
        "A function which runs a number of flips, and returns energy and "
        "magnetization");
  py::class_<Single_Result>(m, "Single_Result")
      .def(py::init<>())
      .def_readwrite("time", &Single_Result::time)
      .def_readwrite("energy", &Single_Result::energy)
      .def_readwrite("magnetization", &Single_Result::magnetization)
      .def_readwrite("up_spins", &Single_Result::up_spins)
      .def_readwrite("down_spins", &Single_Result::down_spins);
}
