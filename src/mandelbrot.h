#pragma once
#include "globals.h"

int mandelbrot(const double cr, const double ci, const int maxIterations);
void processMandelbrot(WindowParameters* const wp, const UserPreferences* const up);
inline double mapToReal(const int x, const double minR, const double maxR, const WindowParameters* const wp);
inline double mapToImaginary(const int y, const double minI, const double maxI, const WindowParameters* const wp);