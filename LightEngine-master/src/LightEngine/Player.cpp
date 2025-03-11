#include "Player.h"

#include <iostream>
// boutons des manettes
#define JOYSTICK_X sf::Joystick::getAxisPosition(0, sf::Joystick::X);
#define JOYSTICK_Y sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
#define BOUTON_C sf::Joystick::isButtonPressed(0, 0);
#define BOUTON_X sf::Joystick::isButtonPressed(0, 1);
#define BOUTON_O sf::Joystick::isButtonPressed(0, 2);
#define BOUTON_T sf::Joystick::isButtonPressed(0, 3);
#define BOUTON_L1 sf::Joystick::isButtonPressed(0, 4);
#define BOUTON_R1 sf::Joystick::isButtonPressed(0, 5);
#define BOUTON_L2 sf::Joystick::isButtonPressed(0, 6);
#define BOUTON_R2 sf::Joystick::isButtonPressed(0, 7);
#define BOUTON_SHARE sf::Joystick::isButtonPressed(0, 8);
#define BOUTON_START sf::Joystick::isButtonPressed(0, 9);
#define BOUTON_L3 sf::Joystick::isButtonPressed(0, 10);
#define BOUTON_R3 sf::Joystick::isButtonPressed(0, 11);
#define BOUTON_PS sf::Joystick::isButtonPressed(0, 12);
#define BOUTON_PAVE sf::Joystick::isButtonPressed(0, 13);
// stop
void Player::OnCollision(Entity* other)
{
	std::cout << "Player::OnCollision" << std::endl;
}

void Player::OnUpdate() {
	float PositiveJoystickSensibility = 20.0f; // la sensibilité du joystick
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	if (jumping) {
		if (pos.x < OldX) {
			jumping = false;
		}
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			GoToPosition(pos.x+10, pos.y, 200);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			GoToPosition(pos.x - 10, pos.y, 200);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setGravityForce(-200);
		}
		if (sf::Joystick::isConnected(0)) {
			float joystickX = JOYSTICK_X;
			float joystickY = JOYSTICK_Y;
			bool X = BOUTON_X;
			if (joystickX > PositiveJoystickSensibility) {
				GoToPosition(pos.x + 10, pos.y, 200);
			}
			if (joystickX < -PositiveJoystickSensibility) {
				GoToPosition(pos.x - 10, pos.y, 200);
			}
			if (X) {
				if (jumping) return;
				OldX = pos.x;
				jumping = true;
				setGravityForce(-200);
			}
		}

}