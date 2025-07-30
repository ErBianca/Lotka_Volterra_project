#include "lotka_volterra.hpp"

namespace pf {

// Costruttore con parametri iniziali
Simulation::Simulation(double newA, double newB, double newC, double newD,
                       double newx_0, double newy_0, double new_dt)
    : A(newA), B(newB), C(newC), D(newD), x_0(newx_0), y_0(newy_0), dt(new_dt) {
}

void pf::Simulation::setUseRK4(bool flag) { useRK4 = flag; }

// Getter degli elementi dei vector
const std::vector<double> &Simulation::gett() const { return t; }
const std::vector<double> &Simulation::getx() const { return data.x; }
const std::vector<double> &Simulation::gety() const { return data.y; }
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

  if (x_i <= 0.0 || y_i <= 0.0) {
    std::cerr << "Errore: una delle due specie si è estinta. Simulazione "
                 "interrotta.\n";
    return;
  }

  double H_i = -D * std::log(x_i) + C * x_i + B * y_i - A * std::log(y_i);

  data.x.push_back(x_i);
  data.y.push_back(y_i);
  data.H.push_back(H_i);

  x_0 = x_i;
  y_0 = y_i;
}

void pf::Simulation::evolveRK4() {
  auto dxdt = [this](double x, double y) { return A * x - B * x * y; };
  auto dydt = [this](double x, double y) { return C * x * y - D * y; };

  double k1x = dxdt(x_0, y_0);
  double k1y = dydt(x_0, y_0);

  double k2x = dxdt(x_0 + 0.5 * dt * k1x, y_0 + 0.5 * dt * k1y);
  double k2y = dydt(x_0 + 0.5 * dt * k1x, y_0 + 0.5 * dt * k1y);

  double k3x = dxdt(x_0 + 0.5 * dt * k2x, y_0 + 0.5 * dt * k2y);
  double k3y = dydt(x_0 + 0.5 * dt * k2x, y_0 + 0.5 * dt * k2y);

  double k4x = dxdt(x_0 + dt * k3x, y_0 + dt * k3y);
  double k4y = dydt(x_0 + dt * k3x, y_0 + dt * k3y);

  double x_next = x_0 + (dt / 6.0) * (k1x + 2 * k2x + 2 * k3x + k4x);
  double y_next = y_0 + (dt / 6.0) * (k1y + 2 * k2y + 2 * k3y + k4y);

  if (x_next <= 1e-6 || y_next <= 1e-6) {
    std::cerr << "Errore: una delle due specie si è estinta. Simulazione "
                 "interrotta.\n";
    return;
  }

  double H_next =
      -D * std::log(x_next) + C * x_next + B * y_next - A * std::log(y_next);

  data.x.push_back(x_next);
  data.y.push_back(y_next);
  data.H.push_back(H_next);

  x_0 = x_next;
  y_0 = y_next;
}

// metodo per ripetere la simulazione n volte per ottenere n+1 triple di valori
void Simulation::runSimulation(int n) {
  for (int i = 1; i <= n; ++i) {
    if (useRK4) {
      evolveRK4();
    } else {
      evolve();
    }
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

void pf::Simulation::computeStatistics() const {
  if (data.x.empty()) {
    std::cout << "No data available.\n";
    return;
  }

  auto [min_x, max_x] = std::minmax_element(data.x.begin(), data.x.end());
  auto [min_y, max_y] = std::minmax_element(data.y.begin(), data.y.end());
  auto [min_H, max_H] = std::minmax_element(data.H.begin(), data.H.end());

  double mean_x =
      std::accumulate(data.x.begin(), data.x.end(), 0.0) / data.x.size();
  double mean_y =
      std::accumulate(data.y.begin(), data.y.end(), 0.0) / data.y.size();
  double mean_H =
      std::accumulate(data.H.begin(), data.H.end(), 0.0) / data.H.size();

  std::ofstream out("Statistics.txt");
  out << std::fixed << std::setprecision(6);

  out << "STATISTICS:\n\n";
  out << "Prey (x):\n"
      << "  Min: " << *min_x << "\n"
      << "  Max: " << *max_x << "\n"
      << "  Mean: " << mean_x << "\n\n";

  out << "Predator (y):\n"
      << "  Min: " << *min_y << "\n"
      << "  Max: " << *max_y << "\n"
      << "  Mean: " << mean_y << "\n\n";

  out << "Integral of motion (H):\n"
      << "  Min: " << *min_H << "\n"
      << "  Max: " << *max_H << "\n"
      << "  Mean: " << mean_H << "\n";

  out.close();
}

} // namespace pf
