#pragma once
#include "globals.h"

void updateSDLWindow(const WindowParameters* const wp);
void quitSDL(WindowParameters* wp);
int allocateVideoBuffer(WindowParameters* const wp);
int initialiseSDL(WindowParameters* const wp);