#include "bird_player.h"

BirdPlayer::BirdPlayer(TextureManager* _texture_manager, Vector2 initialPos)
{
	texture_manager = _texture_manager;
	sprite = new Sprite
	{
		Transform{
			Vector2{
				initialPos.x,
				initialPos.y,
			},
			Vector2{
				40,
				40
			}
		},
		texture_manager->get_texture(TextureManager::TEXTURE_FLAPPY_BIRD_UP_WING),
	};
}

void BirdPlayer::update(double elapsedTime)
{
	movement_update(elapsedTime);
}

void BirdPlayer::movement_update(double elapsedTime) {

	auto& inputManager = InputContainer::GetInstance();  // Get singleton instance
	if (inputManager.is_key_pressed(InputContainer::InputKey::RIGHT_ARROW)) {
		sprite->transform.position += Vector2{1, 0} * 1000000 * elapsedTime;
	}
}

Transform* BirdPlayer::get_transform()
{
	return &sprite->transform;
}
