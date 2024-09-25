#pragma once
#include "structs.h"
#include <SDL.h>

void game();
bool init();
	bool load_init_resources();
void input();
void update(float deltatime);
void render();
	void draw_backgroung();
	void draw_sprites();
void kill();