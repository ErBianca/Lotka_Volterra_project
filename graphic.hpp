#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

namespace pf {
void plotLissajous(const std::vector<double> &x, const std::vector<double> &y,
                   double A, double B, double C, double D);
}

#endif