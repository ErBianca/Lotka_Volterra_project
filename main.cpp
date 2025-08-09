#include <iostream>
#include <limits> 

#include "lotka_volterra.hpp"
#include "graphic.hpp"


int main() {
  // Inserimento parametri A, B, C, D
  std::cout << "Insert the parameters A, B, C and D separated by a space\n";
  double newA, newB, newC, newD;
  bool valid_input = false;

  while (!valid_input) {
    std::cin >> newA >> newB >> newC >> newD;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Error: please insert only numbers for the parameters!\n";
      continue;
    }

    if (newA <= 0 || newB <= 0 || newC <= 0 || newD <= 0) {
      std::cout << "Error: all parameters must be positive!\n";
    } else {
      valid_input = true;
    }
  }

  // Inserimento valori iniziali x0 e y0
  std::cout << "Write the initial number of prey (x_0) and the initial number "
               "of predators (y_0) separated by a space\n";
  double newx_0, newy_0;
  bool valid_input2 = false;

  while (!valid_input2) {
    std::cin >> newx_0 >> newy_0;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout
          << "Error: please insert only numbers for the initial values!\n";
      continue;
    }

    if (newx_0 <= 0 || newy_0 <= 0) {
      std::cout << "Error: all parameters must be positive!\n";
    } else {
      valid_input2 = true;
    }
  }

  // Scelta del metodo di integrazione
  std::cout << "Choose integration method:\n";
  std::cout << "1 - Euler method\n";
  std::cout << "2 - Runge-Kutta 4th order (RK4)\n";
  int method_choice;
  std::cin >> method_choice;

  // Creazione oggetto Simulation con il costruttore parametrico
  pf::Simulation simulation(newA, newB, newC, newD, newx_0, newy_0);

  if (method_choice == 2) {
    simulation.setUseRK4(true);
  }
  // Scrive le coordinate di equilibrio su file
  simulation.e2_x();
  simulation.e2_y();
  simulation.writeCoordinates();

  // Imposta la durata della simulazione
  std::cout << "What is the duration of the simulation?\n";
  double duration;
  std::cin >> duration;

  int steps = static_cast<int>(duration / 0.001);
  simulation.initializeVectors();
  simulation.runSimulation(steps);
  simulation.checkHStability(1e-4);
  simulation.writeResults();
  simulation.computeStatistics();
  pf::plotLissajous(simulation.getx(), simulation.gety(), newA, newB, newC, newD);
  pf::plotTimeEvolution(simulation.gett(), simulation.getx(), simulation.gety());
  std::cout << "Simulation completed, results written in ValueList.txt, "
               "Statistics.txt and "
               "e_2Coordinates.txt\n";

  return 0;
}
