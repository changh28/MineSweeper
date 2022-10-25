
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "GUI.h"

int initSDL(){

	int result;
	if(SDL_WasInit(SDL_INIT_EVERYTHING) != 0){
		std::cerr << "SDL is already initialized\n";
		result = 1;
	}else if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		throw "Error: Failed to initialize SDL\n";
		result = -1;
	}else{
		std::cerr << "SDL initialized\n";
		result = 0;
	}
	return result;
}

int stopSDL(){

	int result;
	if(SDL_WasInit(SDL_INIT_EVERYTHING) == 0){
		std::cerr << "SDL is not operating\n";
		result = 0;
	}else{
		SDL_Quit();
		std::cerr << "SDL terminated\n";
		result = 1;
	}
	return result;
}

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


