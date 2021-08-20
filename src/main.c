#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "SDLController.h"
#include "userInteraction.h"
#include "mandelbrot.h"

int main(void)
{
	const int FPS = 30;
	const int FRAME_TIME = 1000 / FPS;
	int isRunning;
	WindowParameters wp;
	UserPreferences up;

	// Show the default preferences and provide an option to change the preferences before starting
	getUserPreferences(&up);
	wp.WINDOW_WIDTH = up.windowWidth;
	wp.WINDOW_HEIGHT = up.windowHeight;
	wp.window = NULL;
	wp.renderer = NULL;
	wp.texture = NULL;
	wp.videoBuffer = NULL;

	// Allocate video memory
	if (allocateVideoBuffer(&wp) != 0)
	{
		return -1;
	}

	// Process the pixel values in the video buffer
	processMandelbrot(&wp, &up);

	// Initialise SDL
	if (initialiseSDL(&wp) != 0) {
		printf("SDL Initialization failed!\n");
		SDL_Quit();
		return -1;
	}

	// Main Loop
	isRunning = 1;
	while (isRunning != 0) {
		SDL_Event event;
		Uint32 frameStart = SDL_GetTicks();

		if (SDL_PollEvent(&event) && event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = 0;
		}

		updateSDLWindow(&wp);

		Uint32 frameDelay = SDL_GetTicks() - frameStart;
		if (frameDelay < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - frameDelay);
		}
	}

	quitSDL(&wp);
	return 0;
}