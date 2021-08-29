#pragma once
#include "globals.h"

static int mandelbrot(const double cr, const double ci, const int maxIterations);
static double mapToReal(const int x, const double minR, const double maxR, const WindowParameters* const wp);
static double mapToImaginary(const int y, const double minI, const double maxI, const WindowParameters* const wp);

void processMandelbrot(WindowParameters* const wp, const UserPreferences* const up);