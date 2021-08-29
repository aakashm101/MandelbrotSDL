#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "userInteraction.h"

static const int WINDOW_WIDTH_MIN = 800;
static const int WINDOW_HEIGHT_MIN = 600;
static const int MIN_ITERATIONS = 1000;

static const int WINDOW_WIDTH_MAX = 1920;
static const int WINDOW_HEIGHT_MAX = 1080;
static const int MAX_ITERATIONS = 500000;

static const int WINDOW_WIDTH_DEFAULT = 1024;
static const int WINDOW_HEIGHT_DEFAULT = 576;
static const int MAX_ITERATIONS_DEFAULT = 4000;
static const int USE_SINGLE_COLOR_DEFAULT = 0;
static const int INVERT_COLORS_DEFAULT = 0;

static void setDefaultPreferences(UserPreferences* const up)
{
	up->windowWidth = WINDOW_WIDTH_DEFAULT;
	up->windowHeight = WINDOW_HEIGHT_DEFAULT;
	up->invertColors = INVERT_COLORS_DEFAULT;
	up->maxIterations = MAX_ITERATIONS_DEFAULT;
	up->useSingleColor = USE_SINGLE_COLOR_DEFAULT;
	return;
}

static void displayPreferences(const UserPreferences* const up)
{
	const char defaultstr[] = "(default)";
	printf("TIP: Press Escape while the SDL window is in focus to close the SDL window.\n\n");
	printf("Current preferences:\n");
	printf("1.Window width = %d %s\n", up->windowWidth, (up->windowWidth == WINDOW_WIDTH_DEFAULT) ? defaultstr : "");
	printf("2.Window height = %d %s\n", up->windowHeight, (up->windowHeight == WINDOW_HEIGHT_DEFAULT) ? defaultstr : "");
	printf("3.Max Iterations = %d %s\n", up->maxIterations, (up->maxIterations == MAX_ITERATIONS_DEFAULT) ? defaultstr : "");
	printf("4.Invert Colors = %s %s\n", (up->invertColors == 0) ? "NO": "YES", (up->invertColors == INVERT_COLORS_DEFAULT) ? defaultstr : "");
	printf("5.Use Single Color = %s %s\n", (up->useSingleColor == 0) ? "NO" : "YES", (up->useSingleColor == USE_SINGLE_COLOR_DEFAULT) ? defaultstr : "");
	printf("NOTE: By default, the mandelbrot fractal will be plotted in different colors on a black background.\n\n");
	return;
}

static void displayMainUserPreferences(void)
{
	printf("Options:\n");
	printf("1.Start.\n");
	printf("2.Set default preferences.\n");
	printf("3.Change preferences.\n");
	printf("4.Exit\n");
	return;
}

void getUserPreferences(UserPreferences* const up)
{
	int c;
	int loop;

	const int MAIN_PREFERENCE_OPTIONS[] = { 1, 2, 3, 4 };
	const int MAIN_PREFERENCE_OPTIONS_COUNT = sizeof(MAIN_PREFERENCE_OPTIONS) / sizeof(int);
	
	setDefaultPreferences(up);

	loop = 1;
	while (loop)
	{
		clearTerminal();
		displayPreferences(up);
		displayMainUserPreferences();
		
		c = getIntUserChoice("Enter the option number: ", MAIN_PREFERENCE_OPTIONS, MAIN_PREFERENCE_OPTIONS_COUNT);

		switch (c)
		{
			// If option 1 (Start), start processing
			case 1:
			{
				printf("Starting...\n");
				loop = 0;
				break;
			}

			// If option 2 (Set default preferences), clear the terminal, reset preferences and show the preferences
			case 2:
			{
				printf("Default preferences set.\n");
				waitForKeyPress();
				break;
			}

			// If option 3 (Change preferences), clear the terminal, show the preferences and get the preference number to change the corresponding preference
			case 3:
			{
				clearTerminal();
				displayPreferences(up);
				changePreferences(up);
				break;
			}

			// If option 4 (Exit), exit the program
			case 4:
			{
				exit(0);
			}
		}
	}
}

static void changePreferences(UserPreferences* const up)
{
	const int CHANGE_PREFERENCE_OPTIONS[] = { 1, 2, 3, 4, 5 };
	const int CHANGE_PREFERENCE_OPTIONS_COUNT = sizeof(CHANGE_PREFERENCE_OPTIONS) / sizeof(int);
	int c;
	int temp;

	c = getIntUserChoice("Enter preference number to change: ", CHANGE_PREFERENCE_OPTIONS, CHANGE_PREFERENCE_OPTIONS_COUNT);

	switch (c)
	{
		// If option 1 (Window width), get the window width value from user (If input is invalid use defaults)
		case 1:
		{
			printf("Enter window width [%d to %d]: ", WINDOW_WIDTH_MIN, WINDOW_WIDTH_MAX);
			scanf(" %4d", &temp);
		
			if (temp >= WINDOW_WIDTH_MIN && temp <= WINDOW_WIDTH_MAX)
			{
				up->windowWidth = temp;
			}
			else
			{
				printf("Invalid input. Using default value %d\n", WINDOW_WIDTH_DEFAULT);
				up->windowWidth = WINDOW_WIDTH_DEFAULT;
				waitForKeyPress();
			}
			break;
		}

		// If option 2 (Window height), get the window height value from user (If input is invalid use defaults)
		case 2:
		{
			printf("Enter window height [%d to %d]: ", WINDOW_HEIGHT_MIN, WINDOW_HEIGHT_MAX);
			scanf(" %d", &temp);
		
			if (temp >= WINDOW_HEIGHT_MIN && temp <= WINDOW_HEIGHT_MAX)
			{
				up->windowHeight = temp;
			}
			else
			{
				printf("Invalid input. Using default value %d\n", WINDOW_HEIGHT_DEFAULT);
				up->windowHeight = WINDOW_HEIGHT_DEFAULT;
				waitForKeyPress();
			}
			break;
		}

		// If option 3 (Max iterations), get the maxIterations value from user (If input is invalid use defaults)
		case 3:
		{
			printf("Enter max iterations [%d to %d]: ", MIN_ITERATIONS, MAX_ITERATIONS);
			scanf(" %d", &temp);

			if (temp >= MIN_ITERATIONS && temp <= MAX_ITERATIONS)
			{
				up->maxIterations = temp;
			}
			else
			{
				printf("Invalid input. Using default value %d\n", MAX_ITERATIONS_DEFAULT);
				up->maxIterations = MAX_ITERATIONS_DEFAULT;
				waitForKeyPress();
			}
			break;
		}

		// If option 4 (Invert colors), get yes/no value from user (If input is invalid use defaults)
		case 4:
		{
			c = getYesNoUserChoice("Invert Colors? [Y/N]: ");

			if (c == 1)
			{
				up->invertColors = 1;
			}
			else if(c == 0)
			{
				up->invertColors = 0;
			}
			break;
		}

		// If option 5 (Use single color), get yes/no value from user (If input is invalid use defaults)
		case 5:
		{
			c = getYesNoUserChoice("Use Single Color? [Y/N]: ");

			if (c == 1)
			{
				up->useSingleColor = 1;
			}
			else if (c == 0)
			{
				up->useSingleColor = 0;
			}
			break;
		}
	}
}

static int getIntUserChoice(const char* const prompt, const int* const options, const int noOfOptions)
{
	int choice;

	while(1)
	{
		printf("%s", prompt);
		scanf(" %d", &choice);

		for (int i = 0; i < noOfOptions; i++)
		{
			if (choice == *(options+i))
			{
				return choice;
			}
		}

		printf("Invalid Input! Accepted inputs are: ");
		for (int i = 0; i < noOfOptions; i++)
		{
			printf("%d%s", *(options+i), i < noOfOptions - 1 ? ", " : "\n\n");
		}
	}
}

static int getYesNoUserChoice(const char* const prompt)
{
	char c;
	while(1)
	{
		printf("%s", prompt);
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y')
		{
			return 1;
		}
		else if (c == 'N' || c == 'n')
		{
			return 0;
		}
		else
		{
			printf("Invalid Input!\n");
		}
	}
}

inline static void waitForKeyPress(void)
{
	printf("Press any key...");
	fseek(stdin, 0, SEEK_END);
	getchar();
	return;
}

inline static void clearTerminal(void)
{
	#ifdef _WIN32
	system("cls");
	#endif // _WIN32

	#ifdef linux
	system("clear");
	#endif // linux
	return;
}
