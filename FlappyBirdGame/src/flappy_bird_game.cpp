// FlappyBirdGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "global_funcs.h"
#include <SDL.h>

int main(int argc, char* args[])
{
	game();

    return 0;
}

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

void game()
{
	init();

	// Clear the window to white
	SDL_SetRenderDrawColor(renderer, 155, 55, 255, 255);
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_Rect winder_rect{ 0, 0, w, h};
	SDL_RenderFillRect(renderer, &winder_rect);
	SDL_RenderPresent(renderer);

	system("pause");

	kill();
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	load_resources();

	return true;
}

bool load_resources()
{
	// Load bitmap into surface
	SDL_Surface* buffer = SDL_LoadBMP("../res/imgs/yellowbird-upflap.bmp");
	if (!buffer) {
		std::cout << "Error loading image: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create texture
	texture = SDL_CreateTextureFromSurface(renderer, buffer);
	// Free surface as it's no longer needed
	SDL_FreeSurface(buffer);
	buffer = NULL;
	if (!texture) {
		std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
		return false;
	}
}

void kill()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	texture = NULL;
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}