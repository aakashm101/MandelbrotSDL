#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <limits.h>
#include "globals.h"
#include "userInteraction.h"

const int WINDOW_WIDTH_MIN = 800;
const int WINDOW_HEIGHT_MIN = 600;
const int MIN_ITERATIONS = 1000;

const int WINDOW_WIDTH_MAX = 1920;
const int WINDOW_HEIGHT_MAX = 1080;
const int MAX_ITERATIONS = 500000;

const int WINDOW_WIDTH_DEFAULT = 1024;
const int WINDOW_HEIGHT_DEFAULT = 576;
const int MAX_ITERATIONS_DEFAULT = 4000;
const int USE_SINGLE_COLOR_DEFAULT = 0;
const int INVERT_COLORS_DEFAULT = 0;

void setDefaultPreferences(UserPreferences* const up)
{
	up->windowWidth = WINDOW_WIDTH_DEFAULT;
	up->windowHeight = WINDOW_HEIGHT_DEFAULT;
	up->invertColors = INVERT_COLORS_DEFAULT;
	up->maxIterations = MAX_ITERATIONS_DEFAULT;
	up->useSingleColor = USE_SINGLE_COLOR_DEFAULT;
	return;
}

void displayPreferences(const UserPreferences* const up)
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

void getUserPreferences(UserPreferences* const up)
{
	char c;
	int loop;
	long temp;

	setDefaultPreferences(up);

	loop = 1;
	while (loop)
	{
		clearTerminal();
		displayPreferences(up);

		// Fetch the option number from the user
		do
		{
			// Display the options to the user
			printf("Options:\n");
			printf("1.Start.\n");
			printf("2.Set default preferences.\n");
			printf("3.Change preferences.\n");
			printf("4.Exit\n");

			printf("Enter the option number: ");
			c = getchar();
			flushInputBuffer();
			printf("\n");
		} while (c != '1' && c != '2' && c != '3' && c != '4');
		printf("\n");

		switch (c)
		{
			// If option 1 (Start), start processing
			case '1':
			{
				printf("Starting...\n");
				loop = 0;
				break;
			}

			// If option 2 (Set default preferences), clear the terminal, reset preferences and show the preferences
			case '2':
			{
				printf("Default preferences set.\n");
				printf("Press any key...");
				getchar();
				break;
			}

			// If option 3 (Change preferences), clear the terminal, show the preferences and get the preference number to change the corresponding preference
			case '3':
			{
				clearTerminal();
				displayPreferences(up);
				changePreferences(up);
				break;
			}

			// If option 4 (Exit), exit the program
			case '4':
			{
				exit(0);
			}
		}
	}
}

void changePreferences(UserPreferences* const up)
{
	char c;
	long temp;

	do
	{
		printf("Enter preference number to change: ");
		c = getchar();
		flushInputBuffer();
	} while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5');

	switch (c)
	{
		// If option 1 (Window width), get the window width value from user (If input is invalid use defaults)
		case '1':
		{
			printf("Enter window width [%d to %d]: ", WINDOW_WIDTH_MIN, WINDOW_WIDTH_MAX);
			scanf(" %d", &temp);
			flushInputBuffer();
		
			if (temp >= WINDOW_WIDTH_MIN && temp <= WINDOW_WIDTH_MAX)
			{
				up->windowWidth = temp;
			}
			else
			{
				printf("Invalid input. Using default value %d\n", WINDOW_WIDTH_DEFAULT);
				up->windowWidth = WINDOW_WIDTH_DEFAULT;
				printf("Press any key...");
				getchar();
			}
			break;
		}

		// If option 2 (Window height), get the window height value from user (If input is invalid use defaults)
		case '2':
		{
			printf("Enter window height [%d to %d]: ", WINDOW_HEIGHT_MIN, WINDOW_HEIGHT_MAX);
			scanf(" %d", &temp);
			flushInputBuffer();
		
			if (temp >= WINDOW_HEIGHT_MIN && temp <= WINDOW_HEIGHT_MAX)
			{
				up->windowHeight = temp;
			}
			else
			{
				printf("Invalid input. Using default value %d\n", WINDOW_HEIGHT_DEFAULT);
				up->windowHeight = WINDOW_HEIGHT_DEFAULT;
				printf("Press any key...");
				getchar();
			}
			break;
		}

		// If option 3 (Max iterations), get the maxIterations value from user (If input is invalid use defaults)
		case '3':
		{
			printf("Enter max iterations [%d to %d]: ", MIN_ITERATIONS, MAX_ITERATIONS);
			scanf(" %d", &temp);
			flushInputBuffer();

			if (temp >= MIN_ITERATIONS && temp <= MAX_ITERATIONS)
			{
				up->maxIterations = temp;
			}
			else
			{
				printf("Invalid input. Using default value %d\n", MAX_ITERATIONS_DEFAULT);
				up->maxIterations = MAX_ITERATIONS_DEFAULT;
				printf("Press any key...");
				getchar();
			}
			break;
		}

		// If option 4 (Invert colors), get yes/no value from user (If input is invalid use defaults)
		case '4':
		{
			printf("Invert Colors? [Y/N]: ");
			c = getchar();
			flushInputBuffer();

			if (c == 'Y' || c == 'y')
			{
				up->invertColors = 1;
			}
			else if (c == 'N' || c == 'n')
			{
				up->invertColors = 0;
			}
			else
			{
				printf("Invalid input. Using default value %s\n", INVERT_COLORS_DEFAULT ? "Y" : "N");
				up->invertColors = 0;
				printf("Press any key...");
				getchar();
			}
			break;
		}

		// If option 5 (Use single color), get yes/no value from user (If input is invalid use defaults)
		case '5':
		{
			printf("Use Single Color? [Y/N]: ");
			c = getchar();
			flushInputBuffer();

			if (c == 'Y' || c == 'y')
			{
				up->useSingleColor = 1;
			}
			else if (c == 'N' || c == 'n')
			{
				up->useSingleColor = 0;
			}
			else
			{
				printf("Invalid input. Using default value %s\n", INVERT_COLORS_DEFAULT ? "Y" : "N");
				up->useSingleColor = 0;
				printf("Press any key...");
				getchar();
			}
			break;
		}
	}
}

void flushInputBuffer(void)
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);	// Flush stdin
	return;
}

void clearTerminal(void)
{
	#ifdef _WIN32
		system("cls");
	#endif // _WIN32

	#ifdef linux
		system("clear");
	#endif // linux
	return;
}
