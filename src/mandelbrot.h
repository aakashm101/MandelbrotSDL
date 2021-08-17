#pragma once
#include "globals.h"

void processMandelbrot(WindowParameters* wp, UserPreferences* up);
int mandelbrot(double cr, double ci, int maxIterations);
inline double mapToReal(int x, double minR, double maxR, const WindowParameters* const wp);
inline double mapToImaginary(int y, double minI, double maxR, const WindowParameters* const wp);