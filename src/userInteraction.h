#pragma once
#include "globals.h"

void setDefaultPreferences(UserPreferences* const up);
void displayPreferences(const UserPreferences* const up);
void getUserPreferences(UserPreferences* const up);
void changePreferences(UserPreferences* const up);
char getCharacterInput(const char* const prompt, const char* const options, const int optionCount);
void waitForKeyPress(void);
void clearTerminal(void);