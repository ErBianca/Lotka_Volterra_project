#ifndef LOTKA_VOLTERRA_HPP
#define LOTKA_VOLTERRA_HPP

#include <cmath>
#include <fstream>
#include <vector>

namespace pf {

class Simulation {
 private:
  double A{};    // 1.1
  double B{};    // 0.4
  double C{};    // 0.1
  double D{};    // 0.4
  double x_0{};  // 80
  double y_0{};  // 20
  double dt{0.001};

  std::vector<double> x = {};
  std::vector<double> y = {};
  std::vector<double> H = {};
  std::vector<double> t = {};

 public:
  // methods to set the parameters A,B,C,D and the initial values x_0 and y_0
  void setValueA(double newA);
  void setValueB(double newB);
  void setValueC(double newC);
  void setValueD(double newD);
  void setx_0(double newx_0);
  void sety_0(double newy_0);

  // methods to get elements inside the vectors (useful for the tests)
  const std::vector<double>& getx() const;
  const std::vector<double>& gety() const;
  const std::vector<double>& getH() const;
  const std::vector<double>& gett() const;

  // method to get the coordinates of the point of equilibrium e_2
  double e2_x();
  double e2_y();

  // method to write the coordinates of e_2 in a txt file
  void writeCoordinates();

  // method to initialize the vector x,y,H and t with the initial values
  void initializeVectors();

  // method to calculate the new values of x,y and H after dt
  void evolve();

  // method to repete the simulation n times to obtain n+1 triples of values
  void runSimulation(int n);

  // writing in a txt file the values inside the vectors x,y,H and t
  void writeResults();
};
}  // namespace pf

#endif