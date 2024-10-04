#include "bird_player.h"

BirdPlayer::BirdPlayer(TextureManager* _texture_manager, Vector2 initialPos)
{
	rigidbody = Rigidbody{};
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

	// move
	//
	auto& input_manager = InputContainer::GetInstance();  // Get singleton instance
	if (input_manager.is_key_pressed(InputContainer::InputKey::INPUTKEY_RIGHT_ARROW)) {
		sprite->transform.position += Vector2{1, 0} * 100 * elapsedTime;
	}

	// Jump
	//
	if (input_manager.is_key_pressed(InputContainer::InputKey::INPUTKEY_SPACE)) {
		// TODO: invert to "rigidbody.reset_forces"
		PhysicsSystem::GetInstance().reset_forces(this->get_rigidbody());
		PhysicsSystem::GetInstance().add_force(this->get_rigidbody(), Vector2{ 0, 30 });
	}
}
