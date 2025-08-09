#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

namespace pf {
void plotLissajous(const std::vector<double> &x, const std::vector<double> &y,
                   double A, double B, double C, double D);

void plotTimeEvolution(const std::vector<double> &t,
                       const std::vector<double> &x,
                       const std::vector<double> &y);
} // namespace pf

#endif