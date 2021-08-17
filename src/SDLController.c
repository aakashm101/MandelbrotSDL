#include "SDLController.h"

int initialiseSDL(WindowParameters* const wp)
{
	SDL_SetMainReady();

	// Initialise SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Init Error. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	// Create SDL Window
	wp->window = SDL_CreateWindow("Mandelbrot Fractal using SDL - by Aakash.M", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wp->WINDOW_WIDTH, wp->WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC);
	if (!wp->window)
	{
		printf("SDL_CreateWindow Error. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	// Create the renderer
	wp->renderer = SDL_CreateRenderer(wp->window, -1, SDL_RENDERER_ACCELERATED);
	if (!wp->renderer)
	{
		printf("SDL_CreateRenderer Error. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	// Create a texture
	wp->texture = SDL_CreateTexture(wp->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, wp->WINDOW_WIDTH, wp->WINDOW_HEIGHT);
	if (!wp->texture)
	{
		printf("SDL_CreateTexture Error. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if(!wp->videoBuffer)
	{
		printf("Video memory not allocated before calling initialiseSDL()! Calling allocateVideoBuffer()");
		allocateVideoBuffer(wp);
	}

	return 0;
}

int allocateVideoBuffer(WindowParameters* wp)
{
	// Allocate memory for the video buffer
	wp->videoBuffer = calloc(wp->WINDOW_WIDTH * wp->WINDOW_HEIGHT, sizeof(Uint32));
	if (!wp->videoBuffer)
	{
		printf("Video Buffer memory allocation error.");
		SDL_Quit();
		return -1;
	}
	return 0;
}

void updateSDLWindow(WindowParameters* const wp)
{
	SDL_UpdateTexture(wp->texture, NULL, wp->videoBuffer, wp->WINDOW_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(wp->renderer, wp->texture, NULL, NULL);
	SDL_RenderPresent(wp->renderer);
	return;
}

void quitSDL(WindowParameters* const wp)
{
	if (!wp->videoBuffer) free(wp->videoBuffer);
	SDL_DestroyRenderer(wp->renderer);
	SDL_DestroyWindow(wp->window);
	SDL_Quit();
	exit(0);
}
