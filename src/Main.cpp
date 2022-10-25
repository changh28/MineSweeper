
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "GUI.h"

int main(int argv, char** args) {

	// initialize SDL
	initSDL();

	// create the window and surface (its 2D image)
	SDL_Window* window = SDL_CreateWindow( \
	"test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	// fill the surface and update
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface -> format, 0xAA,0xBB,0xCC));
	SDL_UpdateWindowSurface(window);

	// get the window to stay up
	SDL_Delay(5000);

	// close the window
	SDL_DestroyWindow(window);

	// quit SDL
	stopSDL();

	return 0;
}