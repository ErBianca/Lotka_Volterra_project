#include "lotka_volterra.hpp"

namespace pf {

// Costruttore con parametri iniziali per i coefficienti e condizioni iniziali
Simulation::Simulation(double newA, double newB, double newC, double newD,
                       double newx_0, double newy_0, double new_dt)
    : A(newA), B(newB), C(newC), D(newD), x_0(newx_0), y_0(newy_0), dt(new_dt) {
}

// Imposta se utilizzare il metodo Runge-Kutta 4 (RK4) per l'evoluzione
void Simulation::setUseRK4(bool flag) { useRK4 = flag; }

// Getter per il vettore dei tempi
const std::vector<double> &Simulation::gett() const { return t; }
// Getter per il vettore delle popolazioni delle prede
const std::vector<double> &Simulation::getx() const { return data.x; }
// Getter per il vettore delle popolazioni dei predatori
const std::vector<double> &Simulation::gety() const { return data.y; }
// Getter per il vettore dell'integrale primo
const std::vector<double> &Simulation::getH() const { return data.H; }

// Calcola la coordinata x del punto di equilibrio e_2 (preda)
double Simulation::e2_x() const { return D / C; }

// Calcola la coordinata y del punto di equilibrio e_2 (predatore)
double Simulation::e2_y() const { return A / B; }

// Scrive le coordinate del punto di equilibrio e_2 in un file di testo
void Simulation::writeCoordinates() const {
  std::ofstream File("e_2Coordinates.txt");
  File << e2_x() << std::endl << e2_y() << std::endl;
  File.close();
}

// Inizializza i vettori delle popolazioni, della funzione H e del tempo con i
// valori iniziali
void Simulation::initializeVectors() {
  data.x.push_back(x_0);
  data.y.push_back(y_0);
  // Calcolo iniziale della funzione H (integrale del moto)
  data.H.push_back(-D * log(x_0) + C * x_0 + B * y_0 - A * log(y_0));
  t.push_back(0.0);
}

// Calcola i nuovi valori di x, y e H dopo un intervallo dt usando la formula
// semplificata
void Simulation::evolve() {
  // Variabili relative rispetto al punto di equilibrio e_2
  double x_0_rel = x_0 / e2_x();
  double y_0_rel = y_0 / e2_y();

  // Aggiornamento con la formula relativa (Euler esplicito)
  double x_i_rel = x_0_rel + A * (1.0 - y_0_rel) * x_0_rel * dt;
  double y_i_rel = y_0_rel + D * (x_0_rel - 1.0) * y_0_rel * dt;

  // Conversione alle variabili assolute
  double x_i = x_i_rel * e2_x();
  double y_i = y_i_rel * e2_y();

  // Se sotto soglia → estinzione
  bool extinct_x = (x_i <= 1e-6);
  bool extinct_y = (y_i <= 1e-6);
  if (extinct_x)
    x_i = 0.0;
  if (extinct_y)
    y_i = 0.0;

  // Calcolo H: in caso di estinzione è infinito
  double H_i;
  if (extinct_x || extinct_y) {
    H_i = std::numeric_limits<double>::infinity(); 
  } else {
    H_i = -D * std::log(x_i) + C * x_i + B * y_i - A * std::log(y_i);
  }

  // Salvataggio dei nuovi dati
  data.x.push_back(x_i);
  data.y.push_back(y_i);
  data.H.push_back(H_i);

  // Aggiornamento stato
  x_0 = x_i;
  y_0 = y_i;
}

void Simulation::evolveRK4() {
  // Definizione delle derivate dx/dt e dy/dt per il sistema di equazioni
  auto dxdt = [this](double x, double y) { return A * x - B * x * y; };
  auto dydt = [this](double x, double y) { return C * x * y - D * y; };

  // Calcolo dei coefficienti k1
  double k1x = dxdt(x_0, y_0);
  double k1y = dydt(x_0, y_0);

  // Calcolo dei coefficienti k2
  double k2x = dxdt(x_0 + 0.5 * dt * k1x, y_0 + 0.5 * dt * k1y);
  double k2y = dydt(x_0 + 0.5 * dt * k1x, y_0 + 0.5 * dt * k1y);

  // Calcolo dei coefficienti k3
  double k3x = dxdt(x_0 + 0.5 * dt * k2x, y_0 + 0.5 * dt * k2y);
  double k3y = dydt(x_0 + 0.5 * dt * k2x, y_0 + 0.5 * dt * k2y);

  // Calcolo dei coefficienti k4
  double k4x = dxdt(x_0 + dt * k3x, y_0 + dt * k3y);
  double k4y = dydt(x_0 + dt * k3x, y_0 + dt * k3y);

  // Calcolo dei nuovi valori di x e y con la formula RK4
  double x_next = x_0 + (dt / 6.0) * (k1x + 2 * k2x + 2 * k3x + k4x);
  double y_next = y_0 + (dt / 6.0) * (k1y + 2 * k2y + 2 * k3y + k4y);

  // Controllo di estinzione
  bool extinct_x = (x_next <= 1e-6);
  bool extinct_y = (y_next <= 1e-6);
  if (extinct_x)
    x_next = 0.0;
  if (extinct_y)
    y_next = 0.0;

  // Calcolo del valore di H
  double H_next;
  if (extinct_x || extinct_y) {
    H_next = std::numeric_limits<double>::infinity(); 
  } else {
    H_next =
        -D * std::log(x_next) + C * x_next + B * y_next - A * std::log(y_next);
  }

  // Salvataggio dei dati
  data.x.push_back(x_next);
  data.y.push_back(y_next);
  data.H.push_back(H_next);

  // Aggiornamento stato iniziale
  x_0 = x_next;
  y_0 = y_next;
}

// Esegue la simulazione per n passi
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

// Scrive i dati temporali e delle popolazioni su file
void Simulation::writeResults() const {
  if (data.x.empty() || t.empty()) {
    std::cout << "Nessun dato disponibile.\n";
    return;
  }

  std::ofstream out("ValueList.txt");
  out << std::fixed << std::setprecision(6);

  out << "TIME\t\tPREY(x)\t\tPREDATOR(y)\t\tH\n\n";

  for (size_t m = 0; m < data.x.size(); ++m) {
    out << t[m] << "\t" << data.x[m] << "\t" << data.y[m] << "\t" << data.H[m]
        << "\n";
  }

  out.close();
}

// Calcola statistiche minime, massime e medie
void Simulation::computeStatistics() const {
  if (data.x.empty()) {
    std::cout << "Nessun dato disponibile.\n";
    return;
  }

  auto [min_x, max_x] = std::minmax_element(data.x.begin(), data.x.end());
  auto [min_y, max_y] = std::minmax_element(data.y.begin(), data.y.end());
  auto [min_H, max_H] = std::minmax_element(data.H.begin(), data.H.end());

  double mean_x = std::accumulate(data.x.begin(), data.x.end(), 0.0) / 
                  static_cast<double>(data.x.size());
  double mean_y = std::accumulate(data.y.begin(), data.y.end(), 0.0) / 
                  static_cast<double>(data.y.size());
  double mean_H = std::accumulate(data.H.begin(), data.H.end(), 0.0) / 
                  static_cast<double>(data.H.size());

  std::ofstream out("Statistics.txt");
  out << std::fixed << std::setprecision(6);

  out << "STATISTICHE:\n\n";
  out << "Prede (x):\n"
      << "  Min: " << *min_x << "\n"
      << "  Max: " << *max_x << "\n"
      << "  Media: " << mean_x << "\n\n";

  out << "Predatori (y):\n"
      << "  Min: " << *min_y << "\n"
      << "  Max: " << *max_y << "\n"
      << "  Media: " << mean_y << "\n\n";

  out << "Integrale del moto (H):\n"
      << "  Min: " << *min_H << "\n"
      << "  Max: " << *max_H << "\n"
      << "  Media: " << mean_H << "\n";

  out.close();
}

// Controlla la stabilità dell’integrale del moto
bool Simulation::checkHStability(double tolerance) const {
  if (data.H.empty()) {
    std::cerr << "Nessun dato disponibile per controllare la stabilità.\n";
    return false;
  }

  double H0 = data.H.front();
  double maxDeviation = 0.0;

  for (double Hval : data.H) {
    double deviation = std::fabs(Hval - H0) / std::fabs(H0);
    if (deviation > maxDeviation) {
      maxDeviation = deviation;
    }
  }

  std::ofstream out("H_Stability.txt");
  out << std::fixed << std::setprecision(6);
  out << "H iniziale: " << H0 << "\n";
  out << "Massima deviazione relativa: " << maxDeviation << "\n";
  out << "Tolleranza: " << tolerance << "\n";
  out << "Stabile: " << (maxDeviation <= tolerance ? "SI" : "NO") << "\n";
  out.close();

  return maxDeviation <= tolerance;
}

} // namespace pf
