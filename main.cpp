#include <iostream>

#include "lotka_volterra.hpp"

int main() {
  pf::Simulation simulation1;

  // setting the parameters A (prey grow rate), B (prey death rate), C
  // (predator grow rate) and D (predator death rate)
  std::cout << "Insert the parameters A,B,C and D separated by a space\n";
  double newA1, newB1, newC1, newD1;

  bool valid_input1 = false;

  while (valid_input1 == false) {
    std::cin >> newA1 >> newB1 >> newC1 >> newD1;

    // controlling a non numeric input
    if (std::cin.fail()) {
      std::cin.clear(); // resetting the error state of cin
      std::cin.ignore(
          std::numeric_limits<std::streamsize>::max(),
          '\n'); // ignoring the current input until the next newline
      std::cout << "Error: please insert only numbers for the parameters!\n";
      continue; // going back to the start of the while cycle
    }

    // controlling non positive input
    if (newA1 <= 0 || newB1 <= 0 || newC1 <= 0 || newD1 <= 0) {
      std::cout << "Error: all parameters must be positive!\n";
    } else {
      valid_input1 = true; // exiting the cycle, if the input is valid
    }
  }

  simulation1.setValueA(newA1);
  simulation1.setValueB(newB1);
  simulation1.setValueC(newC1);
  simulation1.setValueD(newD1);

  simulation1.e2_x();
  simulation1.e2_y();
  simulation1.writeCoordinates();

  // setting the initial numbers of prey and predators
  std::cout << "Write the initial number of prey (x_0) and the initial number "
               "of predators (y_0) separated by a space\n";
  double newx_01, newy_01;

  bool valid_input2 = false;

  while (valid_input2 == false) {
    std::cin >> newx_01 >> newy_01;

    // controlling a non numeric input
    if (std::cin.fail()) {
      std::cin.clear(); // resetting the error state of cin
      std::cin.ignore(
          std::numeric_limits<std::streamsize>::max(),
          '\n'); // ignoring the current input until the next newline
      std::cout
          << "Error: please insert only numbers for the initial values!\n";
      continue; // going back to the start of the while cycle
    }

    // controlling non positive input
    if (newx_01 <= 0 || newy_01 <= 0) {
      std::cout << "Error: all parameters must be positive!\n";
    } else {
      valid_input2 = true; // exiting the cycle, if the input is valid
    }
  }

  simulation1.setx_0(newx_01);
  simulation1.sety_0(newy_01);

  // setting the duration of the simulation
  std::cout << "What is the duration of the simulation?\n";
  double duration;
  std::cin >> duration;

  int steps = static_cast<int>(duration / 0.001);
  simulation1.initializeVectors();
  simulation1.runSimulation(steps);
  simulation1.writeResults();

  std::cout << "Simulation completed, results written in ValueList.txt and in "
               "e_2Coordinates.txt\n";
  std::cout
      << "If one of the species got extinct the value of the integral is "
         "undefined,\n it has been arbitrarly set to 0\n";
}
