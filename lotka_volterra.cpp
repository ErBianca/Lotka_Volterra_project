#include "lotka_volterra.hpp"

void pf::Simulation::setValueA(double newA) { A = newA; };
void pf::Simulation::setValueB(double newB) { B = newB; };
void pf::Simulation::setValueC(double newC) { C = newC; };
void pf::Simulation::setValueD(double newD) { D = newD; };

void pf::Simulation::setx_0(double newx_0) { x_0 = newx_0; }
void pf::Simulation::sety_0(double newy_0) { y_0 = newy_0; }

const std::vector<double> &pf::Simulation::getx() const { return x; }
const std::vector<double> &pf::Simulation::gety() const { return y; }
const std::vector<double> &pf::Simulation::getH() const { return H; }
const std::vector<double> &pf::Simulation::gett() const { return t; }

double pf::Simulation::e2_x() { return D / C; }
double pf::Simulation::e2_y() { return A / B; }

// method to write the coordinates of e_2 in a txt file
void pf::Simulation::writeCoordinates() {
  std::ofstream File("e_2Coordinates.txt");
  File << e2_x() << std::endl << e2_y() << std::endl;
  File.close();
}

// method to initialize the vector x,y,H and t with the initial values
void pf::Simulation::initializeVectors() {
  x.push_back(x_0);
  y.push_back(y_0);
  H.push_back(-D * log(x_0) + C * x_0 + B * y_0 - A * log(y_0));
  t.push_back(0.0);
}

// method to calculate the new values of x,y and H after dt
void pf::Simulation::evolve() {
  double x_0_rel = x_0 / e2_x();
  double y_0_rel = y_0 / e2_y();

  double x_i_rel = x_0_rel + (A - B * y_0_rel) * x_0_rel * dt;
  double y_i_rel = y_0_rel + (C * x_0_rel - D) * y_0_rel * dt;

  double x_i = x_i_rel * e2_x();
  double y_i = y_i_rel * e2_y();

  double H_i;

  // controlling the case in which on specie goes extinct by setting an
  // arbitrary really small number



  if (x_i < 1e-6) {
    x_i = 0;
  }
  if (y_i < 1e-6) {
    y_i = 0;
  }
  
  /*Setting the integral=0 in case of an extinct specie*/
  
  if ((x_i < 1e-6) | (y_i < 1e-6)) {
    H_i=0;
  } else {
    H_i = -D * log(x_i) + C * x_i + B * y_i - A * log(y_i);
  }

  x.push_back(x_i);
  y.push_back(y_i);
  H.push_back(H_i);

  x_0 = x_i;
  y_0 = y_i;
}

// method to repete the simulation n times to obtain n triples of values
void pf::Simulation::runSimulation(int n) {
  for (int i{1}; i <= n; ++i) {
    evolve();
    t.push_back(dt * i);
  }
}

// writing in a txt file the values inside the vectors
void pf::Simulation::writeResults() {
  std::ofstream File("ValueList.txt");

  for (size_t m{0}; m < x.size(); ++m) {
    File << std::fixed << t[m] << " " << std::fixed << x[m] << " " << std::fixed
         << y[m] << " " << std::fixed << H[m] << '\n';
  }
  File.close();
};
