#include "Player.h"
#include "CircleCollider.h"

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

void Player::OnInitialize() {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new CircleCollider(pos,GetRadius());
}

void Player::OnCollision(Entity* other)
{
	Collider* coll = dynamic_cast<Collider*>(other);
	if (m_collider->isColliding(coll)) {
		std::cout << "player colide";
	}
}
void Player::Parry() {

}

void Player::OnUpdate() {
	float PositiveJoystickSensibility = 20.0f; // la sensibilité du joystick
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	float joystickX = JOYSTICK_X;
	float joystickY = JOYSTICK_Y;
	bool X = BOUTON_X;
	bool R2 = BOUTON_R2;
	    if (jumping) {
		    if (pos.y >= OldY) {
				jumping = false;
		    }
	    }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickX > PositiveJoystickSensibility) {
			GoToPosition(pos.x+10, pos.y, 200);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
			GoToPosition(pos.x - 10, pos.y, 200);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) {
			if (jumping) return;
			OldY = pos.y;
			jumping = true;
			setGravityForce(-200);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)|| R2) {
			Parry();
		}
}


/*----------------------------------------poubelles-------------------------------------------*/
	/*if (sf::Joystick::isConnected(0)) {
			if (joystickX > PositiveJoystickSensibility) {
				GoToPosition(pos.x + 10, pos.y, 200);
			}
			if (joystickX < -PositiveJoystickSensibility) {
				GoToPosition(pos.x - 10, pos.y, 200);
			}
			if (X) {
				if (jumping) return;
				OldY = pos.y;
				jumping = true;
				setGravityForce(-200);
			}
		}*/
//------------------------------------------------------------------------------------------------