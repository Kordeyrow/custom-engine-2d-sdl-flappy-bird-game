#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <set>
#include "InputContainer.h"
#include "texture_manager.h"
#include "bird_player.h"
#include "IUpdate.h"
#include "global_funcs.h"
#include "Physics/PhysicsSystem.h"
#include "Physics/Rigidbody.h"
#include <SDL.h>


int main(int argc, char* args[])
{
	run();
	close();
    return 0;
}

// SDL
SDL_Window* window;
SDL_Renderer* renderer;

// Systems
PhysicsSystem& physics = PhysicsSystem::GetInstance();

// Managers
TextureManager* texture_manager;

// Containers
InputContainer& input_manager = InputContainer::GetInstance();

// Gameobjects
std::vector<Sprite*> sprite_list;
std::set<IUpdate*> enabled_gameobjects;
std::set<IUpdate*> disabled_gameobjects;
BirdPlayer* bird_player;


void run() {
	if (init() == false) {
		return;
	}
	while (input_manager.user_quitted() == false) {
		update();
		render();
	}
}

void close()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	texture_manager->kill();
	texture_manager = nullptr;

	SDL_Quit();
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

	window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
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

	//// load init_resources
	// 
	// init vectors_reserve
	sprite_list.reserve(10);
	//
	if (texture_manager->load_init_textures() == false) {
		return false;
	}

	physics.init();

	// create bird_player
	bird_player = new BirdPlayer(texture_manager, Vector2{ 0, 0 });
	// TODO: 
	enabled_gameobjects.insert(bird_player);
	// TODO: create sprite factory (to centralize "push_back")
	sprite_list.push_back(bird_player->sprite);
	// TODO: 
	physics.add((Rigidbody*)bird_player);

	return true;
}

void update() {
	auto elapsedTime = calculate_elapsed_time();
	input_manager.update();
	physics.update(elapsedTime);
	update_enabled_gameobjects(elapsedTime);
}

void render()
{
	draw_backgroung();
	draw_sprites();
	SDL_RenderPresent(renderer);
}

void update_enabled_gameobjects(double elapsedTime) {
	for (auto& obj : enabled_gameobjects) {
		obj->update(elapsedTime);
	}
}

static double calculate_elapsed_time() {
	static uint32_t prev = SDL_GetTicks();
	static uint32_t now = 0;
	now = SDL_GetTicks();
	double elapsedTime = (now - prev) / 1000.0f; // Convert to seconds.
	prev = SDL_GetTicks();
	return elapsedTime;
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
	for (auto& s : sprite_list) {
		auto& t = s->transform;
		SDL_Rect r{ (int)t.position.x, (int)t.position.y, (int)t.size.x, (int)t.size.y };
		SDL_RenderCopyEx(renderer, s->texture, NULL, &r, s->rotation, NULL, s->flip);
	}
}
