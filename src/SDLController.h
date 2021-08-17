#pragma once
#include "globals.h"

int allocateVideoBuffer(WindowParameters* wp);
int initialiseSDL(WindowParameters* const wp);
void updateSDLWindow(WindowParameters* const wp);
void quitSDL(WindowParameters* const wp);