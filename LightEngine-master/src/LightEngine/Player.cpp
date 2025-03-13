#include "Player.h"
#include "CircleCollider.h"

#include "PlayerAction.h"
#include "PlayerCondition.h"

#include "TestScene.h"

#include "Debug.h"
#include "Managers.h"

#include "SpriteSheet.h"
#include "Animation.h"

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
#define BOUTON_R2 sf::Joystick::isButtonPressed(0, 6);
#define BOUTON_L2 sf::Joystick::isButtonPressed(0, 7);
#define BOUTON_SHARE sf::Joystick::isButtonPressed(0, 8);
#define BOUTON_START sf::Joystick::isButtonPressed(0, 9);
#define BOUTON_L3 sf::Joystick::isButtonPressed(0, 10);
#define BOUTON_R3 sf::Joystick::isButtonPressed(0, 11);
#define BOUTON_PS sf::Joystick::isButtonPressed(0, 12);
#define BOUTON_PAVE sf::Joystick::isButtonPressed(0, 13);
// stop
#define DASH 300

#define COLLIDER_RADIUS 32

void Player::OnInitialize() {

	SetTag(TestScene::Tag::player);
	SpriteSheet* spriteSheet = new SpriteSheet(this);
	Animation* animTest1 = new Animation("Test1", sf::Vector2i(102, 96), 2, 0.5f, true);
	spriteSheet->addAnimation(animTest1);
	Animation* animTest2 = new Animation("Test2", sf::Vector2i(102, 96), 2, 0.5f, false);
	spriteSheet->addAnimation(animTest2);
	spriteSheet->setAnimation(1);

	m_sprite = spriteSheet;

	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new CircleCollider(pos, COLLIDER_RADIUS);
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
		{//Dash
			auto transition = pIdle->CreateTransition(State::dash);
			auto condition = transition->AddCondition<PlayerCondition_IsDash>();
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
		{//Dash
			auto transition = pWalking->CreateTransition(State::dash);
			auto condition = transition->AddCondition<PlayerCondition_IsDash>();
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
		{//Dash
			auto transition = pJumping->CreateTransition(State::dash);
			auto condition = transition->AddCondition<PlayerCondition_IsDash>();
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
		{//Dash
			auto transition = pParrying->CreateTransition(State::dash);
			auto condition = transition->AddCondition<PlayerCondition_IsDash>();
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
			{//Dash
				auto transition = pAttacking->CreateTransition(State::dash);
				auto condition = transition->AddCondition<PlayerCondition_IsDash>();
			}
		}
	}
	//Dash
	{
		Action<Player>* pDash = mpStateMachine->CreateAction<PlayerAction_Idle>(State::dash);
		{//walking
			auto transition = pDash->CreateTransition(State::walking);
			auto condition = transition->AddCondition<PlayerCondition_IsWalking>();
		}
		{//jumping
			auto transition = pDash->CreateTransition(State::jumping);
			auto condition = transition->AddCondition<PlayerCondition_IsJumping>();
		}
		{//parrying
			auto transition = pDash->CreateTransition(State::parrying);
			auto condition = transition->AddCondition<PlayerCondition_IsParrying>();
		}
		{//attacking
			auto transition = pDash->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<PlayerCondition_IsShooting>();
		}
		{//idle
			auto transition = pDash->CreateTransition(State::idle);
			auto condition = transition->AddCondition<PlayerCondition_IsIdle>();
		}

	}
	mpStateMachine->SetState(State::idle);
}

void Player::onCollision(Entity* other)
{
	if (!m_isAlive) return;
	if (!m_Parrying) {
		std::cout << "carrote";
	}
}

void Player::parry() {
	m_parryCooldown = 2.f;
	m_Parrying = true;
	std::cout << "going to parry !" << std::endl;
}

void Player::Attack() {
	m_shootCooldown = 2.f;
	m_ammo -= 1;
	std::cout << m_ammo;
	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), m_lastDir,this, false);
	bullet->setMass(1);
	bullet->setGravityDirection(sf::Vector2f(0, 1));

}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case walking: return "walking";
	case jumping: return "jumping";
	case parrying: return "parrying";
	case attacking: return "attacking";
	case dash: return "Dashing";
	default: return "Unknown";
	}
}

void Player::TakeDamage(int damage) {
	if (m_Parrying) return;
	m_life -= damage;
	std::cout << m_life<<std::endl;
}

void Player::AddBullet(int bullet)
{
	m_ammo += bullet;
}

void Player::DecreaseCD(float dt)
{
	m_parryCooldown -= dt;
	m_shootCooldown -= dt;
	m_dashCooldown -= dt;
}

void Player::HandleInput()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	float PositiveJoystickSensibility = 20.0f; // la sensibilit� du joystick
	float joystickX = JOYSTICK_X;
	float joystickY = JOYSTICK_Y;
	bool X = BOUTON_X;
	bool R2 = BOUTON_R2;
	bool L2 = BOUTON_L2;
	bool R1 = BOUTON_R1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickX > PositiveJoystickSensibility) {
		m_lastDir = { 1,0 };
		mpStateMachine->SetState(State::walking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
		m_lastDir = { -1,0 };
		mpStateMachine->SetState(State::walking);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) && !m_jumping) {
		m_OldY = pos.y;
		mpStateMachine->SetState(State::jumping);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || L2) {
		if (m_parryCooldown <= 0) mpStateMachine->SetState(State::parrying);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		if (m_parryCooldown <= 0) m_life--;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || R2) {
		if (m_shootCooldown <= 0) mpStateMachine->SetState(State::attacking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || R1) {
		if (m_dashCooldown <= 0) {
		mpStateMachine->SetState(State::dash);
		}
	}
}

void Player::CheckPlayerStates()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	if (m_parryTime) m_parryTime -= dt;
	if (GetPosition().y >= m_OldY && m_jumping) {
		m_jumping = false;
	}
	if (m_parryTime <= 0) {
		m_Parrying = false;
		m_parryTime = PARRY_DURATION;
	}
	if (pos.y >= m_OldY && m_jumping) {
		m_jumping = false;
	}
	if (m_life <= 0) {
		m_life = 0;
		m_isAlive = false;
	}
}

void Player::PlayerMove()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();
	float currentFriction;
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
		if (m_jumping) {
			m_velocity.x = m_velocity.x - 3;
		}
		m_velocity.x -= currentFriction * dt;
		if (m_velocity.x < 0) m_velocity.x = 0;
	}
	else if (m_velocity.x < 0) {
		if (m_jumping) {
			m_velocity.x = m_velocity.x +3;
		}
		m_velocity.x += currentFriction * dt;
		if (m_velocity.x > 0) m_velocity.x = 0;
	}
	pos.x += m_velocity.x * dt;
	SetPosition(pos.x, pos.y);
}

void Player::OnUpdate() {
	if (m_life <= 0) { m_isAlive = false; Destroy(); }
	if (!m_isAlive) return;

	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	DecreaseCD(dt);
	CheckPlayerStates();
	HandleInput();
	PlayerMove();

	mpStateMachine->Update();
	const char* stateName = GetStateName((Player::State)mpStateMachine->GetCurrentState());
	std::string life = std::to_string(m_life);
	Debug::DrawText(GetPosition().x, GetPosition().y - 175, stateName, 0.5f, 0.5f, sf::Color::Red);
	Debug::DrawText(GetPosition().x, GetPosition().y - 225, life, 0.5f, 0.5f, sf::Color::Red);
	std::cout << stateName;
}