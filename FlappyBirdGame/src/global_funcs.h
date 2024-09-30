#pragma once
#include "structs.h"
#include <SDL.h>

void game();
bool init();
	void init_vectors_reserve();
	bool load_init_resources();
bool input();
float get_deltatime();
	void read_key_down(SDL_Keycode key);
	void read_key_up(SDL_Keycode key);
void update(float deltatime);
void render();
	void draw_backgroung();
	void draw_sprites();
void kill();