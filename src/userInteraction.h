#pragma once
#include "globals.h"

static void setDefaultPreferences(UserPreferences* const up);
static void displayPreferences(const UserPreferences* const up);
static void displayMainUserPreferences(void);
static void changePreferences(UserPreferences* const up);
static void waitForKeyPress(void);
static void clearTerminal(void);
static int getIntUserChoice(const char* const prompt, const int* const options, const int noOfOptions);
static int getYesNoUserChoice(const char* const prompt);

void getUserPreferences(UserPreferences* const up);