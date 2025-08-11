#ifndef LOTKA_VOLTERRA_HPP
#define LOTKA_VOLTERRA_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>

namespace pf {

// Struttura dati per contenere i vettori delle popolazioni e della funzione H
struct Data {
  std::vector<double> x; // popolazione delle prede
  std::vector<double> y; // popolazione dei predatori
  std::vector<double> H; // integrale del moto (funzione conservata)
};

// Classe che simula il sistema di equazioni Lotka-Volterra
class Simulation {
private:
  // Coefficienti del sistema Lotka-Volterra
  double A, B, C, D;

  // Condizioni iniziali per prede (x_0) e predatori (y_0)
  double x_0, y_0;

  // Passo temporale per l'evoluzione
  double dt;

  // Flag per decidere se usare il metodo Runge-Kutta 4 (RK4)
  bool useRK4 = false;

  // Oggetto dati che contiene i vettori delle popolazioni e dell'integrale H
  Data data;

  // Vettore dei tempi corrispondenti ai dati salvati
  std::vector<double> t;

public:
  // Costruttore con parametri iniziali per i coefficienti e condizioni iniziali
  Simulation(double newA, double newB, double newC, double newD,
             double newx_0, double newy_0, double new_dt);

  // Imposta se utilizzare il metodo RK4 per l'evoluzione
  void setUseRK4(bool flag);

  // Getter per il vettore dei tempi
  const std::vector<double> &gett() const;

  // Getter per il vettore della popolazione delle prede
  const std::vector<double> &getx() const;

  // Getter per il vettore della popolazione dei predatori
  const std::vector<double> &gety() const;
  
  // Getter per il vettore dell'integrale primo
  const std::vector<double> &getH() const;

  // Calcola la coordinata x del punto di equilibrio non banale e_2
  double e2_x() const;

  // Calcola la coordinata y del punto di equilibrio non banale e_2
  double e2_y() const;

  // Scrive su file le coordinate del punto di equilibrio e_2
  void writeCoordinates() const;

  // Inizializza i vettori delle popolazioni, di H e del tempo con i valori iniziali
  void initializeVectors();

  // Calcola un passo di evoluzione usando la formula semplificata (Euler esplicito)
  void evolve();

  // Calcola un passo di evoluzione usando il metodo Runge-Kutta di ordine 4 (RK4)
  void evolveRK4();

  // Esegue la simulazione per n passi temporali, scegliendo il metodo di evoluzione
  void runSimulation(int n);

  // Scrive su file i risultati temporali delle popolazioni e di H
  void writeResults() const;

  // Calcola e scrive statistiche minime, massime e medie di x, y e H
  void computeStatistics() const;

  // Controlla se l'integrale del moto H è stabile entro una certa tolleranza
  bool checkHStability(double tolerance) const;
};

} // namespace pf

#endif // LOTKA_VOLTERRA_HPP
