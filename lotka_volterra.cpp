#include "lotka_volterra.hpp"

namespace pf {

// Costruttore con parametri iniziali
Simulation::Simulation(double newA, double newB, double newC, double newD,
                       double newx_0, double newy_0, double new_dt)
    : A(newA), B(newB), C(newC), D(newD), x_0(newx_0), y_0(newy_0), dt(new_dt) {}



// metodo per ottenere il vettore dei tempi
const std::vector<double>& Simulation::gett() const { return t; }

// metodo per ottenere la coordinata x del punto di equilibrio e_2
double Simulation::e2_x() { return D / C; }

// metodo per ottenere la coordinata y del punto di equilibrio e_2
double Simulation::e2_y() { return A / B; }

// metodo per scrivere le coordinate del punto di equilibrio e_2 in un file txt
void Simulation::writeCoordinates() {
  std::ofstream File("e_2Coordinates.txt");
  File << e2_x() << std::endl << e2_y() << std::endl;
  File.close();
}

// metodo per inizializzare i vettori x, y, H e t con i valori iniziali
void Simulation::initializeVectors() {
  data.x.push_back(x_0);
  data.y.push_back(y_0);
  data.H.push_back(-D * log(x_0) + C * x_0 + B * y_0 - A * log(y_0));
  t.push_back(0.0);
}

// metodo per calcolare i nuovi valori di x, y e H dopo un intervallo dt
void Simulation::evolve() {
  double x_0_rel = x_0 / e2_x();
  double y_0_rel = y_0 / e2_y();

  double x_i_rel = x_0_rel + (A - B * y_0_rel) * x_0_rel * dt;
  double y_i_rel = y_0_rel + (C * x_0_rel - D) * y_0_rel * dt;

  double x_i = x_i_rel * e2_x();
  double y_i = y_i_rel * e2_y();
  double H_i;

  // controllo del caso in cui una specie si estingue, impostando un valore molto piccolo
  if (x_i < 1e-6) {
    x_i = 0;
  }
  if (y_i < 1e-6) {
    y_i = 0;
  }

  // imposto l'integrale a 0 nel caso di estinzione di una specie
  if ((x_i < 1e-6) || (y_i < 1e-6)) {
    H_i = 0;
  } else {
    H_i = -D * log(x_i) + C * x_i + B * y_i - A * log(y_i);
  }

  data.x.push_back(x_i);
  data.y.push_back(y_i);
  data.H.push_back(H_i);

  x_0 = x_i;
  y_0 = y_i;
}

// metodo per ripetere la simulazione n volte per ottenere n+1 triple di valori
void Simulation::runSimulation(int n) {
  for (int i = 1; i <= n; ++i) {
    evolve();
    t.push_back(dt * i);
  }
}

// metodo per scrivere i valori contenuti nei vettori x, y, H e t in un file txt
void Simulation::writeResults() {
  std::ofstream File("ValueList.txt");

  for (size_t m = 0; m < data.x.size(); ++m) {
    File << std::fixed << t[m] << " " << std::fixed << data.x[m] << " "
         << std::fixed << data.y[m] << " " << std::fixed << data.H[m] << '\n';
  }

  File.close();
}

}  // namespace pf
