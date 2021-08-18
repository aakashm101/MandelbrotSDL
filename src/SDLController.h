#pragma once
#include "globals.h"

int allocateVideoBuffer(WindowParameters* const wp);
int initialiseSDL(WindowParameters* const wp);
void updateSDLWindow(const WindowParameters* const wp);
void quitSDL(WindowParameters* wp);