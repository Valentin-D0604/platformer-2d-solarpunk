#include "Player.h"

#include <iostream>

void Player::OnCollision(Entity* other)
{
	std::cout << "Player::OnCollision" << std::endl;
}

void Player::OnUpdate() {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			GoToPosition(pos.x+10, pos.y, 200);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			GoToPosition(pos.x - 10, pos.y, 200);
		}
		else if (sf::Joystick::isConnected(0)) {
			float joystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			if (joystickX > 20.f) {
				GoToPosition(pos.x + 10, pos.y, 200);
			}
			if (joystickX < -20.f) {
				GoToPosition(pos.x - 10, pos.y, 200);
			}
		}
}