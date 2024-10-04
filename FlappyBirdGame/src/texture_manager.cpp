#include "texture_manager.h"

TextureManager::TextureManager(SDL_Renderer* _renderer)
{
	renderer = _renderer;
}

bool TextureManager::load_init_textures()
{
	for (TEXTURE_PATH_KEY key : textures_to_load_on_init)
	{
		if (load_texture(key) == nullptr) {
			return false;
		}
	}
	return true;
}

SDL_Texture* TextureManager::get_texture(TEXTURE_PATH_KEY key)
{
	auto iterator = loaded_textures.find(key);
	if (iterator != loaded_textures.end())
		return iterator->second;
	return load_texture(key);
}

SDL_Texture* TextureManager::load_texture(TEXTURE_PATH_KEY key)
{
	// Load bitmap into surface
	SDL_Surface* buffer = SDL_LoadBMP(textures_paths[key]);
	if (!buffer) {
		std::cout << "Error loading image: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	// Create texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, buffer);
	// Free surface as it's no longer needed
	SDL_FreeSurface(buffer);
	buffer = nullptr;
	if (!texture) {
		std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	loaded_textures.emplace(key, texture);

	return texture;
}

void TextureManager::kill()
{
	for (auto& t : loaded_textures) {
		SDL_DestroyTexture(t.second);
	}
	loaded_textures.clear();
}