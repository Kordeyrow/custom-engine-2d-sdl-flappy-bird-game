// FlappyBirdGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <array>
#include <vector>
#include "texture_manager.h"
#include "bird_player.h"
#include "global_funcs.h"
#include <SDL.h>

int main(int argc, char* args[])
{
	game();

    return 0;
}

SDL_Window* window;
SDL_Renderer* renderer;
TextureManager* texture_manager;
BirdPlayer* bird_player;


// config
std::vector<Sprite*> current_sprites;
bool is_running = false;


void game()
{
	// TODO: Expose config using lua
	// TODO: engine module/project ("monobehaviour", update, render, input, events)

	is_running = init();

	while (is_running) {
		input();
		update();
		render();
	}

	kill();

	system("pause");
}

void input()
{

}

void update()
{
	bird_player->Update();
}

void render()
{
	draw_backgroung();
	draw_sprites();
	SDL_RenderPresent(renderer);
}

void draw_backgroung()
{
	// Clear the window to white
	SDL_SetRenderDrawColor(renderer, 155, 55, 255, 255);
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_Rect r{ 0, 0, w, h };
	SDL_RenderFillRect(renderer, &r);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void draw_sprites()
{
	// TODO: sort by z index
	//
	for (auto s : current_sprites) {
		SDL_RenderCopyEx(renderer, s->texture, NULL, &s->rect, s->rotation, NULL, s->flip);
	}
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

	texture_manager = new TextureManager(renderer);

	if (load_init_resources() == false) {
		return false;
	}

	// create bird_player
	bird_player = new BirdPlayer(texture_manager, Vector2{ 0, 0 });

	// TODO: create sprite factory (to centralize "push_back")
	current_sprites.push_back(bird_player->sprite);

	return true;
}

bool load_init_resources()
{
	return texture_manager->load_init_textures();
}


void kill()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	texture_manager->kill();
	texture_manager = nullptr;

	SDL_Quit();
}