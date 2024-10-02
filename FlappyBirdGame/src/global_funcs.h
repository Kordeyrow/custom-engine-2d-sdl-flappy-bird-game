#pragma once
#include "structs.h"
#include <SDL.h>

void run();
void close();

bool init();
void update();
void render();

double calculate_elapsed_time();
void update_enabled_gameobjects(double elapsedTime);

void draw_backgroung();
void draw_sprites();