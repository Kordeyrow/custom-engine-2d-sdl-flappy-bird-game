#pragma once
#include "structs.h"
#include <SDL.h>

void game();
bool init();
	bool load_init_resources();
void input();
void update();
void render();
	void draw_backgroung();
	void draw_sprites();
void kill();