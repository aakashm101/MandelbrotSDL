#pragma once
#include "globals.h"

void setDefaultPreferences(UserPreferences* const up);
void displayPreferences(const UserPreferences* const up);
void getUserPreferences(UserPreferences* const up);
void changePreferences(UserPreferences* const up);
void flushInputBuffer(void);
void clearTerminal(void);