#include <iostream>
#include <limits> // Per std::numeric_limits

#include "lotka_volterra.hpp"

int main() {
  // Inserimento parametri A, B, C, D
  std::cout << "Insert the parameters A, B, C and D separated by a space\n";
  double newA1, newB1, newC1, newD1;
  bool valid_input1 = false;

  while (!valid_input1) {
    std::cin >> newA1 >> newB1 >> newC1 >> newD1;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Error: please insert only numbers for the parameters!\n";
      continue;
    }

    if (newA1 <= 0 || newB1 <= 0 || newC1 <= 0 || newD1 <= 0) {
      std::cout << "Error: all parameters must be positive!\n";
    } else {
      valid_input1 = true;
    }
  }

  // Inserimento valori iniziali x0 e y0
  std::cout << "Write the initial number of prey (x_0) and the initial number "
               "of predators (y_0) separated by a space\n";
  double newx_01, newy_01;
  bool valid_input2 = false;

  while (!valid_input2) {
    std::cin >> newx_01 >> newy_01;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Error: please insert only numbers for the initial values!\n";
      continue;
    }

    if (newx_01 <= 0 || newy_01 <= 0) {
      std::cout << "Error: all parameters must be positive!\n";
    } else {
      valid_input2 = true;
    }
  }

  // Creazione oggetto Simulation con il costruttore parametrico
  pf::Simulation simulation1(newA1, newB1, newC1, newD1, newx_01, newy_01);

  // Scrive le coordinate di equilibrio su file
  simulation1.e2_x();
  simulation1.e2_y();
  simulation1.writeCoordinates();

  // Imposta la durata della simulazione
  std::cout << "What is the duration of the simulation?\n";
  double duration;
  std::cin >> duration;

  int steps = static_cast<int>(duration / 0.001);
  simulation1.initializeVectors();
  simulation1.runSimulation(steps);
  simulation1.writeResults();

  std::cout << "Simulation completed, results written in ValueList.txt and in e_2Coordinates.txt\n";
  std::cout << "If one of the species got extinct the value of the integral is undefined,\n"
               "it has been arbitrarily set to 0\n";

  return 0;
}
