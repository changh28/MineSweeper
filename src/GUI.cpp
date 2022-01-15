/*
 ================================================================================
 Name        : GUI.cpp
 Author      : CHX
 Copyright   : This project must NOT be copied or shared without authorization
 ================================================================================
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SDL.h>
#include "MineBlock.h"
#include "MineMap.h"

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int initSDL(){
	int result;
	if(SDL_WasInit(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL is already initialized\n";
		result = 1;
	}else if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		throw "Error: Failed to initialize SDL\n";
		result = -1;
	}else{
		cout << "SDL initialized\n";
		result = 0;
	}
	return result;
}

int stopSDL(){
	int result;
	if(SDL_WasInit(SDL_INIT_EVERYTHING) == 0){
		cout << "SDL is not operating\n";
		result = 0;
	}else{
		SDL_Quit();
		cout << "SDL terminated\n";
		result = 1;
	}
	return result;
}

int main(int argv, char** args) {
	initSDL();
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface -> format, 0xAA,0xBB,0xCC));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	stopSDL();
	return 0;
}


