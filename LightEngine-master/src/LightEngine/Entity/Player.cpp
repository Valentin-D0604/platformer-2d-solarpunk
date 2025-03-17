#include "Player.h"
#include "../Collision/CircleCollider.h"

#include "../Actions/PlayerAction.h"
#include "../Conditions/PlayerCondition.h"

#include "../Scene/TestScene.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"

#include "../Graphics/SpriteSheet.h"
#include "../Graphics/Animation.h"

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

	m_Sprite = spriteSheet;

	m_Sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_Collider = new CircleCollider(pos, COLLIDER_RADIUS);
	m_Collider->setGizmo(true);
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
	m_ParryCooldown = 2.f;
	m_Parrying = true;
	std::cout << "going to parry !" << std::endl;
	//mpStateMachine->SetState(State::parrying);
}

void Player::Attack() {
	m_ShootCooldown = 2.f;
	m_Ammo -= 1;
	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), m_LastDir,this, false);
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
	m_Life -= damage;
	std::cout << m_Life<<std::endl;
}

void Player::AddBullet(int bullet)
{
	m_Ammo += bullet;
}

void Player::DecreaseCD(float dt)
{
	m_ParryCooldown -= dt;
	m_ShootCooldown -= dt;
	m_DashCooldown -= dt;
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
		m_Velocity.x += m_Acceleration * dt;
		m_LastDir = { 1,0 };
		//mpStateMachine->SetState(State::walking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
		m_Velocity.x -= m_Acceleration * dt;
		m_LastDir = { -1,0 };
		//mpStateMachine->SetState(State::walking);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) && !m_Jumping) {
		m_OldY = pos.y;
		m_Jumping = true;
		setGravityForce(-200);
		//mpStateMachine->SetState(State::jumping);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || L2) {
		if (m_ParryCooldown <= 0)parry();//mpStateMachine->SetState(State::parrying);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		if (m_ParryCooldown <= 0) m_Life--;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || R2) {
		if (m_ShootCooldown <= 0) Attack();//mpStateMachine->SetState(State::attacking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || R1) {
		if (m_DashCooldown <= 0) {
			GoToPosition(pos.x + DASH * m_LastDir.x, pos.y, 1500);
			m_DashCooldown = 2.f;
		}
	}
}

void Player::CheckPlayerStates()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	if (m_ParryTime) m_ParryTime -= dt;
	if (m_ParryTime <= 0) {
		m_Parrying = false;
		m_ParryTime = PARRY_DURATION;
	}
	if (pos.y >= m_OldY && m_Jumping) {
		m_Jumping = false;
	}
	if (m_Life <= 0) {
		m_Life = 0;
		m_IsAlive = false;
	}
}

void Player::PlayerMove()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();
	float currentFriction;
	if (m_Velocity.x > MAX_VELOCITY) {
		m_Velocity.x = MAX_VELOCITY;
	}
	if (m_Jumping) {
		currentFriction = m_AirResistance;
	}
	else {
		currentFriction = m_Friction;
	}
	if (m_Velocity.x > 0) {
		m_Velocity.x -= currentFriction * dt;
		if (m_Velocity.x < 0) m_Velocity.x = 0;
	}
	else if (m_Velocity.x < 0) {
		m_Velocity.x += currentFriction * dt;
		if (m_Velocity.x > 0) m_Velocity.x = 0;
	}
	pos.x += m_Velocity.x * dt;
	SetPosition(pos.x, pos.y);
}

bool Player::isParrying() const
{
	return m_Parrying;
}

void Player::OnUpdate() {
	if (m_Life == 0) m_IsAlive = false;
	if (!m_IsAlive) Destroy();

	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	DecreaseCD(dt);
	CheckPlayerStates();
	HandleInput();
	PlayerMove();

	mpStateMachine->Update();
	const char* stateName = GetStateName((Player::State)mpStateMachine->GetCurrentState());
	std::string life = std::to_string(m_Life);
	Debug::DrawText(GetPosition().x, GetPosition().y - 175, stateName, 0.5f, 0.5f, sf::Color::Red);
	Debug::DrawText(GetPosition().x, GetPosition().y - 225, life, 0.5f, 0.5f, sf::Color::Red);
}