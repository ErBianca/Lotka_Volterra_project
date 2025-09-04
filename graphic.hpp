#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace pf {
std::string shortLabel(double val);

void plotEquilibriumPointGraph(const std::vector<double> &x,
                               const std::vector<double> &y, double A, double B,
                               double C, double D);

void plotTimeEvolution(const std::vector<double> &t,
                       const std::vector<double> &x,
                       const std::vector<double> &y);
} // namespace pf

#endif