#pragma once
#include "globals.h"

void setDefaultPreferences(UserPreferences* up);
void displayPreferences(UserPreferences* up);
void getUserPreferences(UserPreferences* up);
void changePreferences(UserPreferences* up);
void flushInputBuffer(void);
void clearTerminal(void);