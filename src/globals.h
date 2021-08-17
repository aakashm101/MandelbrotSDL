#include <SDL.h>

#pragma once
typedef struct _fComplex 
{ 
    float re; 
    float im; 
} fComplex;

typedef struct _WindowParameters 
{
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Uint32* videoBuffer;
} WindowParameters;

typedef struct _UserPreferences {
    int windowWidth;
    int windowHeight;
    int invertColors;
    int maxIterations;
} UserPreferences;