#include "bird_player.h"

BirdPlayer::BirdPlayer(TextureManager* _texture_manager, Vector2 initialPos)
{
	texture_manager = _texture_manager;
	sprite = new Sprite
	{ 
		SDL_Rect{
			(int) initialPos.x, 
			(int) initialPos.y,
			40,
			40,
		},
		texture_manager->get_texture(TextureManager::TEXTURE_FLAPPY_BIRD_UP_WING),
	};
}

void BirdPlayer::update(float deltatime)
{
	movement_update(deltatime);
}

void BirdPlayer::movement_update(float deltatime) {

	auto& inputManager = InputManager::GetInstance();  // Get singleton instance

	if (inputManager.is_key_pressed(InputManager::InputKey::RIGHT_ARROW)) {
		position.x += 100 * deltatime;
		sprite->rect.x = position.x;
	}
}
