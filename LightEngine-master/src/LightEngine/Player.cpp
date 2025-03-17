#include "Player.h"
#include "RectangleCollider.h"

#include "PlayerAction.h"

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
	m_isAlive = true;
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
	m_collider = new RectangleCollider(pos, {102,96});
	m_collider->setGizmo(true);
	mpStateMachine = new StateMachine<Player>(this, State::Count);
	Action<Player>* pIdle = mpStateMachine->CreateAction<PlayerAction_Idle>(State::idle);
	Action<Player>* pWalking = mpStateMachine->CreateAction<PlayerAction_Walking>(State::walking);
	Action<Player>* pJumping = mpStateMachine->CreateAction<PlayerAction_jumping>(State::jumping);
	Action<Player>* pParrying = mpStateMachine->CreateAction<PlayerAction_Shooting>(State::parrying);
	Action<Player>* pAttacking = mpStateMachine->CreateAction<PlayerAction_Parrying>(State::attacking);
	Action<Player>* pDash = mpStateMachine->CreateAction<PlayerAction_Dash>(State::dash);
	
    mpStateMachine->SetState(State::idle);
}

void Player::onCollision(Entity* other)
{
	if (!m_isAlive) return;
	if (!m_Parrying) {
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
	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), m_lastDir,this, false);
	bullet->setMass(1);
	bullet->setGravityDirection(sf::Vector2f(0, 1));

}

void Player::Jump()
{
	if (m_jumpCooldown <= 0 && m_jumpCount <= m_maxJumps) {
		std::cout << m_jumpCount;
		setGravityForce(-200);
		m_jumpCount += 1;
		m_jumpCooldown = 0.2f;
	}
}

void Player::Dash()
{
	if (m_dashCooldown <= 0 && !m_Dash) {
		m_Dash = true;
		m_DashDuration = 1.f; 
		m_dashCooldown = 1.5f;

		float dashSpeed = 15000.0f;
		m_friction = 0.f;

		mSpeed = dashSpeed;
		mDirection.x = (m_lastDir.x != 0) ? m_lastDir.x : 1;
	}
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
	std::cout << m_life;
}

void Player::AddBuff(int bonus)
{
	if (m_life < m_maxLife && m_ammo < m_maxAmmo) {
		int buff = rand() % 2;
		if (buff == 0) m_ammo += bonus;
		if (buff == 1) m_life += bonus;
	}
	else if(m_life > m_maxLife && m_ammo < m_maxAmmo) {
		m_ammo += bonus;
	}
	else if (m_ammo > m_maxAmmo && m_life < m_maxLife) {
		m_life += bonus;
	}
	else {
		return;
	}
}

void Player::DecreaseCD(float dt)
{
	m_parryCooldown -= dt;
	m_shootCooldown -= dt;
	m_dashCooldown -= dt;
	m_jumpCooldown -= dt;
	if (m_Dash) { m_DashDuration -= dt; }
}

void Player::HandleInput()
{
	float dt = GetDeltaTime();

	float inputX = 0.0f;

	sf::Vector2f pos = GetPosition();
	float PositiveJoystickSensibility = 20.0f; // la sensibilit� du joystick
	float joystickX = JOYSTICK_X;
	float joystickY = JOYSTICK_Y;
	bool X = BOUTON_X;
	bool R2 = BOUTON_R2;
	bool L2 = BOUTON_L2;
	bool R1 = BOUTON_R1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickX > PositiveJoystickSensibility) {
		inputX = 1.0f;
		m_lastDir = { 1,0 };
		mpStateMachine->SetState(State::walking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
		inputX = -1.0f;
		m_lastDir = { -1,0 };
		mpStateMachine->SetState(State::walking);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) && !m_jumping) {
		if (m_jumpCount <=1) m_OldY = pos.y;
		mpStateMachine->SetState(State::jumping);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || L2) {
		if (m_parryCooldown <= 0)mpStateMachine->SetState(State::parrying);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		if (m_parryCooldown <= 0) m_life--;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || R2) {
		if (m_shootCooldown <= 0) mpStateMachine->SetState(State::attacking);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || R1) {
		mpStateMachine->SetState(State::dash);
	}
		bool reversing = (inputX != 0 && inputX != mDirection.x);

		if (inputX != 0 && (!reversing || mSpeed < 100.0f)) {
			mDirection.x = inputX;
			mSpeed += m_acceleration * dt;
		}
		else if (inputX == 0) {
			mSpeed -= m_friction * dt;
		}

		if (reversing && mSpeed > 0) {
			mSpeed -= turnResistance * dt;
			if (mSpeed < 0) mSpeed = 0;
		}

		if (mSpeed > MAX_SPEED) mSpeed = MAX_SPEED;
		if (mSpeed < 0) mSpeed = 0;
}
void Player::CheckPlayerStates()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	if (pos.y >= m_OldY) {
		m_jumping = false;
		m_jumpCount = 0;
	}
	if (m_parryTime) m_parryTime -= dt;
	if (GetPosition().y >= m_OldY && m_jumping) {
		m_jumping = false;
	}
	if (m_parryTime <= 0) {
		m_Parrying = false;
		m_parryTime = PARRY_DURATION;
	}
	if (m_life <= 0) {
		m_life = 0;
		m_isAlive = false;
	}
	if (m_DashDuration <= 0) {
		m_DashDuration = 1.f;
	}
	if (m_Dash) {
		m_DashDuration -= dt;
		if (m_DashDuration <= 0) {
			m_Dash = false;
			mSpeed *= 0.5f; 
			m_friction = 400.f;
		}
	}
}


void Player::PlayerMove()
{
	float dt = GetDeltaTime();
	sf::Vector2f pos = GetPosition();

	pos.x += mDirection.x * mSpeed * dt;

}
bool Player::IsAlive()
{
	if (m_isAlive != 1 && m_isAlive != 0) {
		return false;
	}
	if (m_isAlive)return true;
	return false;
}

bool Player::IsParry()
{
	if (m_Parrying != 1 && m_Parrying != 0) {
		return false;
	}
	return m_Parrying;
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
	std::cout << m_friction;
	mpStateMachine->Update();
	const char* stateName = GetStateName((Player::State)mpStateMachine->GetCurrentState());
	std::string life = std::to_string(m_life);
}

