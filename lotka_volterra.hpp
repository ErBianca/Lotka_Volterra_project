#ifndef LOTKA_VOLTERRA_HPP
#define LOTKA_VOLTERRA_HPP

#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

namespace pf {

// Struct per raggruppare i dati della simulazione
struct SimulationData {
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> H;
};

class Simulation {

public:
  // parametric constructor

  Simulation(double newA = 0.0, double newB = 0.0, double newC = 0.0,
             double newD = 0.0, double newx_0 = 0.0, double newy_0 = 0.0,
             double new_dt = 0.001);

  // methods to get elements inside the vectors (useful for the tests)
  const std::vector<double> &getx() const;
  const std::vector<double> &gety() const;
  const std::vector<double> &getH() const;
  const std::vector<double> &gett() const;

  void setUseRK4(bool flag);

  // method to get the coordinates of the point of equilibrium e_2
  double e2_x();
  double e2_y();

  // method to write the coordinates of e_2 in a txt file
  void writeCoordinates();

  // method to initialize the vector x,y,H and t with the initial values
  void initializeVectors();

  // method to calculate the new values of x,y and H after dt (Euler method)
  void evolve();

  // method to calculate the new values of x,y and H after dt (RK4 method)
  void evolveRK4();

  // method to repete the simulation n times to obtain n+1 triples of values
  void runSimulation(int n);

  // writing in a txt file the values inside the vectors x,y,H and t
  void writeResults();

private:
  double A{};
  double B{};
  double C{};
  double D{};
  double x_0{};
  double y_0{};
  double dt{0.001};

  bool useRK4 = false;

  SimulationData data{};
  std::vector<double> t = {};
};

} // namespace pf

#endif