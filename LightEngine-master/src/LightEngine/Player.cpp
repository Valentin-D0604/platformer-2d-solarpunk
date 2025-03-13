#include "Player.h"
#include "CircleCollider.h"

#include "PlayerAction.h"
#include "PlayerCondition.h"

#include "TestScene.h"

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
#define DASH 200

void Player::OnInitialize() {
	SetTag(TestScene::Tag::player);
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
	std::cout << "carrote";
}

void Player::parry() {
	m_parryCooldown = 2.f;
	m_Parrying = true;
	std::cout << "going to parry !" << std::endl;
	//mpStateMachine->SetState(State::parrying);
}

void Player::Attack() {
	m_shootCooldown = 2.f;
	m_ammo -= 1;
	Bullet* bullet = CreateEntity<Bullet>(10, sf::Color::Cyan);
	bullet->InitBullet(GetPosition(), m_lastDir,this, false);
	bullet->setMass(1);
	bullet->setGravityDirection(sf::Vector2f(0, 1));
	//mpStateMachine->SetState(State::attacking);
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

void Player::TakeDamage(int damage) {
	m_life -= damage;
	std::cout << m_life<<std::endl;
}

void Player::AddBullet(int bullet)
{
	m_ammo += bullet;
}

void Player::OnUpdate() {
	if (m_life == 0) m_isAlive = false;
	if (!m_isAlive) Destroy();

	float PositiveJoystickSensibility = 20.0f; // la sensibilité du joystick
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();
	float currentFriction;
	float joystickX = JOYSTICK_X;
	float joystickY = JOYSTICK_Y;
	bool X = BOUTON_X;
	bool R2 = BOUTON_R2;
	bool L2 = BOUTON_L2;
	bool R1 = BOUTON_R1;

	m_parryCooldown -= dt;
	m_shootCooldown -= dt;
	if (m_parryTime) m_parryTime -= dt;
	if (m_parryTime <= 0) {
		m_Parrying = false;
		m_parryTime = 5.f;
	}
	if (pos.y >= m_OldY && m_jumping) {
		m_jumping = false;
	}
	if (m_life <= 0) {
		m_life = 0;
		m_isAlive = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickX > PositiveJoystickSensibility) {
		m_velocity.x += m_acceleration * dt;
		m_lastDir = { 1,0 };
		//mpStateMachine->SetState(State::walking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
		m_velocity.x -= m_acceleration * dt;
		m_lastDir = { -1,0 };
		//mpStateMachine->SetState(State::walking);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) && !m_jumping) {
		m_OldY = pos.y;
		m_jumping = true;
		setGravityForce(-200);
		//mpStateMachine->SetState(State::jumping);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || L2) {
		if (m_parryCooldown <= 0) parry();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		if (m_parryCooldown <= 0) m_life--;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || R2) {
		if (m_shootCooldown <= 0) Attack();//mpStateMachine->SetState(State::attacking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || R1) {
		GoToPosition(pos.x + DASH * m_lastDir.x, pos.y, 1000);
	}
	if (m_velocity.x > MAX_VELOCITY) {
		m_velocity.x = MAX_VELOCITY;
	}
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
	std::string life = std::to_string(m_life);
	Debug::DrawText(GetPosition().x, GetPosition().y - 175, stateName, 0.5f, 0.5f, sf::Color::Red);
	Debug::DrawText(GetPosition().x, GetPosition().y - 225, life, 0.5f, 0.5f, sf::Color::Red);
}