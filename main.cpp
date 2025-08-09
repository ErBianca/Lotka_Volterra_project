#include <iostream>
#include <limits> 

#include "lotka_volterra.hpp"
#include "graphic.hpp"

int main() {
  // Richiesta e inserimento dei parametri A, B, C, D del modello
  std::cout << "Inserisci i parametri A, B, C e D separati da uno spazio\n";
  double newA, newB, newC, newD;
  bool valid_input = false;

  // Ciclo per validare l'input: deve essere numerico e positivo
  while (!valid_input) {
    std::cin >> newA >> newB >> newC >> newD;

    if (std::cin.fail()) {
      std::cin.clear(); // reset dello stato di errore dello stream
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignora input errato
      std::cout << "Errore: inserisci solo numeri per i parametri!\n";
      continue;
    }

    if (newA <= 0 || newB <= 0 || newC <= 0 || newD <= 0) {
      std::cout << "Errore: tutti i parametri devono essere positivi!\n";
    } else {
      valid_input = true;
    }
  }

  // Richiesta e inserimento delle condizioni iniziali x0 (prede) e y0 (predatori)
  std::cout << "Inserisci il numero iniziale di prede (x_0) e predatori (y_0) separati da uno spazio\n";
  double newx_0, newy_0;
  bool valid_input2 = false;

  // Ciclo per validare l'input delle condizioni iniziali, deve essere numerico e positivo
  while (!valid_input2) {
    std::cin >> newx_0 >> newy_0;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Errore: inserisci solo numeri per i valori iniziali!\n";
      continue;
    }

    if (newx_0 <= 0 || newy_0 <= 0) {
      std::cout << "Errore: tutti i valori devono essere positivi!\n";
    } else {
      valid_input2 = true;
    }
  }

  // Scelta del metodo di integrazione: Euler o Runge-Kutta 4
  std::cout << "Scegli il metodo di integrazione:\n";
  std::cout << "1 - Metodo di Euler\n";
  std::cout << "2 - Runge-Kutta di ordine 4 (RK4)\n";
  int method_choice;
  std::cin >> method_choice;

  // Creazione dell'oggetto Simulation con i parametri e condizioni iniziali
  pf::Simulation simulation(newA, newB, newC, newD, newx_0, newy_0, 0.001);

  // Se scelto RK4, attiva il flag per usarlo
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

  // Calcola il numero di passi di integrazione, passo fisso 0.001
  int steps = static_cast<int>(duration / 0.001);

  // Inizializza i vettori con i valori iniziali
  simulation.initializeVectors();

  // Esegue la simulazione per il numero di passi calcolato
  simulation.runSimulation(steps);

  // Controlla la stabilità dell'integrale del moto H con tolleranza 1e-4
  simulation.checkHStability(1e-4);

  // Scrive i risultati (popolazioni e H) su file
  simulation.writeResults();

  // Calcola e scrive statistiche su popolazioni e integrale
  simulation.computeStatistics();

  std::cout << "Simulazione completata, risultati scritti in ValueList.txt, Statistics.txt e e_2Coordinates.txt\n";

  // Produce i grafici: curva di Lissajous (fase) e evoluzione temporale
  pf::plotLissajous(simulation.getx(), simulation.gety(), newA, newB, newC, newD);
  pf::plotTimeEvolution(simulation.gett(), simulation.getx(), simulation.gety());

  return 0;
}
