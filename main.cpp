#include <iostream>
#include <limits> 

#include "lotka_volterra.hpp"
#include "graphic.hpp"

int main() {
  // Richiesta e inserimento dei parametri A, B, C, D del modello
  std::cout << "Inserisci i parametri A, B, C e D separati da uno spazio\n";
  double newA, newB, newC, newD;

  std::cin >> newA >> newB >> newC >> newD;

  if (std::cin.fail()) {
    std::cerr << "Errore: inserisci solo numeri per i parametri!" << std::endl;
    return 1;
  }

  if (newA <= 0 || newB <= 0 || newC <= 0 || newD <= 0) {
    std::cerr << "Errore: tutti i parametri devono essere positivi!" << std::endl;
    return 1;
  }

  // Richiesta e inserimento delle condizioni iniziali x0 (prede) e y0 (predatori)
  std::cout << "Inserisci il numero iniziale di prede (x_0) e predatori (y_0) separati da uno spazio\n";
  double newx_0, newy_0;
  std::cin >> newx_0 >> newy_0;

  if (std::cin.fail()) {
    std::cerr << "Errore: inserisci solo numeri per i valori iniziali!" << std::endl;
    return 1;
  }

  if (newx_0 <= 0 || newy_0 <= 0) {
    std::cerr << "Errore: tutti i valori devono essere positivi!" << std::endl;
    return 1;
  }

  // Scelta del metodo di integrazione: Euler o Runge-Kutta 4
  std::cout << "Scegli il metodo di integrazione:\n";
  std::cout << "1 - Metodo di Eulero\n";
  std::cout << "2 - Runge-Kutta di ordine 4 (RK4)\n";
  int method_choice;
  std::cin >> method_choice;

  if (std::cin.fail() || (method_choice != 1 && method_choice != 2)) {
    std::cerr << "Errore: scelta del metodo non valida!" << std::endl;
    return 1;
  }

  // Creazione dell'oggetto Simulation con i parametri e condizioni iniziali
  pf::Simulation simulation(newA, newB, newC, newD, newx_0, newy_0, 0.001);

  if (method_choice == 2) {
    simulation.setUseRK4(true);
  }

  // Scrive le coordinate del punto di equilibrio non banale su file
  simulation.e2_x();
  simulation.e2_y();
  simulation.writeCoordinates();

  // Imposta la durata della simulazione richiesta dall'utente
  std::cout << "Qual è la durata della simulazione?\n";
  double duration;
  std::cin >> duration;

  if (std::cin.fail() || duration <= 0) {
    std::cerr << "Errore: la durata deve essere un numero positivo!" << std::endl;
    return 1;
  }

  int steps = static_cast<int>(duration / 0.001);

  simulation.initializeVectors();
  simulation.runSimulation(steps);
  simulation.checkHStability(1e-4);
  simulation.writeResults();
  simulation.computeStatistics();

  std::cout << "Simulazione completata, risultati scritti in ValueList.txt, Statistics.txt e e_2Coordinates.txt\n";

  pf::plotEquilibriumPointGraph(simulation.getx(), simulation.gety(), newA, newB, newC, newD);
  pf::plotTimeEvolution(simulation.gett(), simulation.getx(), simulation.gety());

  return 0;
}
