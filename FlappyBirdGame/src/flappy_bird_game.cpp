#include <iostream>
#include <map>
#include <array>
#include <vector>
#include "texture_manager.h"
#include "bird_player.h"
#include "IUpdate.h"
#include "global_funcs.h"
#include <SDL.h>


int main(int argc, char* args[])
{
	game();

    return 0;
}

// SDL
SDL_Window* window;
SDL_Renderer* renderer;

// Managers
InputManager& inputManager = InputManager::GetInstance();

// Objects
TextureManager* texture_manager;
BirdPlayer* bird_player;
std::vector<Sprite*> sprite_list;
std::vector<IUpdate*> IUpdates_list;


void game()
{
	bool is_running = init();
	while (true) {
		is_running = input();
		if (is_running == false) 
			break;
		update(get_deltatime());
		render();
	}

	kill();

	//system("pause");
}

float get_deltatime() {

	static Uint64 start = SDL_GetPerformanceCounter();
	static Uint64 end = 0;
	end = SDL_GetPerformanceCounter();
	float deltatime = (end - start) / (float)SDL_GetPerformanceFrequency();
	start = SDL_GetPerformanceCounter();
	return deltatime;
}

bool input()
{
	//static const unsigned char* keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	static int mx = -1, my = -1;

	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN:
				read_key_down(e.key.keysym.sym);
			case SDL_KEYUP:
				read_key_up(e.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				mx = e.motion.x;
				my = e.motion.y;
				break;
		}
	}

	inputManager.update();

	return true;
}

void read_key_down(SDL_Keycode key)
{
	switch (key) {
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		default:
			break;
	}
}

void read_key_up(SDL_Keycode key)
{
	switch (key) {
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		default:
			break;
	}
}

void update(float deltatime)
{
	for (auto u : IUpdates_list) {
		u->update(deltatime);
	}
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
	for (auto s : sprite_list) {
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
	IUpdates_list.push_back(bird_player);

	// TODO: create sprite factory (to centralize "push_back")
	sprite_list.push_back(bird_player->sprite);

	return true;
}

bool load_init_resources()
{
	init_vectors_reserve();
	return texture_manager->load_init_textures();
}

void init_vectors_reserve()
{
	sprite_list.reserve(10);
	IUpdates_list.reserve(10);
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
