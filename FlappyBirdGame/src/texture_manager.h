#pragma once
#include <map>
#include <array>
#include <vector>
#include <iostream>
#include <SDL.h>

class TextureManager 
{
public:
	enum TEXTURE_PATH_KEY {
		TEXTURE_FLAPPY_BIRD_UP_WING
	};
	TextureManager(SDL_Renderer* renderer);
	bool load_init_textures();
	SDL_Texture* get_texture(TEXTURE_PATH_KEY key);
	void kill();

private:
	// config
	std::map<TEXTURE_PATH_KEY, const char*> textures_paths{
		{ static_cast<TEXTURE_PATH_KEY>(TEXTURE_FLAPPY_BIRD_UP_WING), "../res/imgs/yellowbird-upflap.bmp" }
	};
	std::array<TEXTURE_PATH_KEY, 1> textures_to_load_on_init{
		static_cast<TEXTURE_PATH_KEY>(TEXTURE_FLAPPY_BIRD_UP_WING)
	};
	// shared
	SDL_Renderer* renderer;
	// runtime
	std::map<TEXTURE_PATH_KEY, SDL_Texture*> loaded_textures;

	SDL_Texture* load_texture(TEXTURE_PATH_KEY key);
};

