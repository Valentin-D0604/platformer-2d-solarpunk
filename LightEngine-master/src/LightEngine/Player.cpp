#include "Player.h"
#include "CircleCollider.h"

#include "PlayerAction.h"
#include "PlayerCondition.h"

#include "Debug.h"

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
	m_collider->setGizmo(true);
	mpStateMachine = new StateMachine<Player>(this, State::Count);
	//idle
	{
		Action<Player>* pIdle = mpStateMachine->CreateAction<PlayerAction_Idle>(State::idle);
		{//walking
			auto transition = pIdle->CreateTransition(State::walking);
			auto condition = transition->AddCondition<PlayerCondition_IsWalking>();
		}
		{//jumping
			auto transition = pIdle->CreateTransition(State::jumping);
			auto condition = transition->AddCondition<PlayerCondition_IsJumping>();
		}
		{//parrying
			auto transition = pIdle->CreateTransition(State::parrying);
			auto condition = transition->AddCondition<PlayerCondition_IsParrying>();
		}
		{//attacking
			auto transition = pIdle->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<PlayerCondition_IsShooting>();
		}

	}
	//walking
	 {
		Action<Player>* pWalking = mpStateMachine->CreateAction<PlayerAction_Walking>(State::walking);
		{//jumping
			auto transition = pWalking->CreateTransition(State::jumping);
			auto condition = transition->AddCondition<PlayerCondition_IsJumping>();
		}
		{//parrying
			auto transition = pWalking->CreateTransition(State::parrying);
			auto condition = transition->AddCondition<PlayerCondition_IsParrying>();
		}
		{//attacking
			auto transition = pWalking->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<PlayerCondition_IsShooting>();
		}
		{//idle
			auto transition = pWalking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<PlayerCondition_IsIdle>();
		}

	}

	//jumping
	{
		Action<Player>* pJumping = mpStateMachine->CreateAction<PlayerAction_jumping>(State::jumping);
		{//walking
			auto transition = pJumping->CreateTransition(State::walking);
			auto condition = transition->AddCondition<PlayerCondition_IsWalking>();
		}
		{//parrying
			auto transition = pJumping->CreateTransition(State::parrying);
			auto condition = transition->AddCondition<PlayerCondition_IsParrying>();
		}
		{//attacking
			auto transition = pJumping->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<PlayerCondition_IsShooting>();
		}
		{//idle
			auto transition = pJumping->CreateTransition(State::idle);
			auto condition = transition->AddCondition<PlayerCondition_IsIdle>();
		}
	}

	//parrying
	{
		Action<Player>* pParrying = mpStateMachine->CreateAction<PlayerAction_Shooting>(State::parrying);
		{//jumping
			auto transition = pParrying->CreateTransition(State::jumping);
			auto condition = transition->AddCondition<PlayerCondition_IsJumping>();
		}
		{//walking
			auto transition = pParrying->CreateTransition(State::walking);
			auto condition = transition->AddCondition<PlayerCondition_IsWalking>();
		}
		{//attacking
			auto transition = pParrying->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<PlayerCondition_IsShooting>();
		}
		{//idle
			auto transition = pParrying->CreateTransition(State::idle);
			auto condition = transition->AddCondition<PlayerCondition_IsIdle>();
		}
	}

	//attacking
	{
		Action<Player>* pAttacking = mpStateMachine->CreateAction<PlayerAction_Parrying>(State::attacking);
		{
			{//jumping
				auto transition = pAttacking->CreateTransition(State::jumping);
				auto condition = transition->AddCondition<PlayerCondition_IsJumping>();
			}
			{//parrying
				auto transition = pAttacking->CreateTransition(State::parrying);
				auto condition = transition->AddCondition<PlayerCondition_IsParrying>();
			}
			{//walking
				auto transition = pAttacking->CreateTransition(State::walking);
				auto condition = transition->AddCondition<PlayerCondition_IsWalking>();
			}
			{//idle
				auto transition = pAttacking->CreateTransition(State::idle);
				auto condition = transition->AddCondition<PlayerCondition_IsIdle>();
			}
		}
	}
	mpStateMachine->SetState(State::idle);
}

void Player::onCollision(Entity* other)
{
		std::cout << "player colide";
}

void Player::parry() {
	//Parry* pro = new Parry(GetPosition(),{50,50});
	Parry* protec = CreateEntity<Parry>(50, sf::Color::Green);
	protec->SetPosition(GetPosition().x-175, GetPosition().y);
	protec->setMass(20);
	protec->setGravityDirection(sf::Vector2f(0, 1));
}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case walking: return "walking";
	case jumping: return "jumping";
	case parrying: return "parrying";
	case attacking: return "attacking";
	default: return "Unknown";
	}
}

void Player::OnUpdate() {
	float PositiveJoystickSensibility = 20.0f; // la sensibilité du joystick
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();
	float joystickX = JOYSTICK_X;
	float joystickY = JOYSTICK_Y;
	bool X = BOUTON_X;
	bool R2 = BOUTON_R2;
	
	if (pos.y >= m_OldY && m_jumping) {
		m_jumping = false;
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickX > PositiveJoystickSensibility) {
			m_velocity.x += m_acceleration * dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
			m_velocity.x -= m_acceleration * dt;
			// GoToPosition(pos.x - 10, pos.y, 200);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) && !m_jumping){
			m_OldY = pos.y;
			m_jumping = true;
			setGravityForce(-200);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)|| R2) {
			parry();
		}

		if (m_velocity.x > MAX_VELOCITY) {
			m_velocity.x = MAX_VELOCITY;
		}

		float currentFriction;
		if (m_jumping) {
			currentFriction = m_airResistance;
		}
		else {
			currentFriction = m_friction;
		}
		if (m_velocity.x > 0) {
			m_velocity.x -= currentFriction * dt;
			if (m_velocity.x < 0) m_velocity.x = 0;
		}
		else if (m_velocity.x < 0) {
			m_velocity.x += currentFriction * dt;
			if (m_velocity.x > 0) m_velocity.x = 0; 
		}

		pos.x += m_velocity.x * dt;
		SetPosition(pos.x, pos.y);

		mpStateMachine->Update();
		const char* stateName = GetStateName((Player::State)mpStateMachine->GetCurrentState());
		std::cout << stateName << std::endl;
		Debug::DrawText(GetPosition().x, GetPosition().y - 175, stateName, 0.5f, 0.5f, sf::Color::Red);
}