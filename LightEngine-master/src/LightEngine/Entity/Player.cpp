#include "../Entity/Player.h"
#include "../Collision/RectangleCollider.h"

#include "../Actions/PlayerAction.h"

#include "../Scene/TestScene.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"

#include "../Entity/Platform.h"
#include "../Graphics/SpriteSheet.h"
#include "../Graphics/Animation.h"

#include <iostream>
// boutons des manettes
#define JOYSTICK_X sf::Joystick::getAxisPosition(0, sf::Joystick::X)
#define JOYSTICK_Y sf::Joystick::getAxisPosition(0, sf::Joystick::Y)
#define BOUTON_C sf::Joystick::isButtonPressed(0, 0)
#define BOUTON_X sf::Joystick::isButtonPressed(0, 1)
#define BOUTON_O sf::Joystick::isButtonPressed(0, 2)
#define BOUTON_T sf::Joystick::isButtonPressed(0, 3)
#define BOUTON_L1 sf::Joystick::isButtonPressed(0, 4)
#define BOUTON_R1 sf::Joystick::isButtonPressed(0, 5)
#define BOUTON_L2 sf::Joystick::isButtonPressed(0, 6)
#define BOUTON_R2 sf::Joystick::isButtonPressed(0, 7)
#define BOUTON_SHARE sf::Joystick::isButtonPressed(0, 8)
#define BOUTON_START sf::Joystick::isButtonPressed(0, 9)
#define BOUTON_L3 sf::Joystick::isButtonPressed(0, 10)
#define BOUTON_R3 sf::Joystick::isButtonPressed(0, 11)
#define BOUTON_PS sf::Joystick::isButtonPressed(0, 12)
#define BOUTON_PAVE sf::Joystick::isButtonPressed(0, 13)
// stop
#define DASH 300

#define COLLIDER_RADIUS 32

void Player::OnInitialize() {
	m_isAlive = true;
	SetTag(TestScene::Tag::player);
	SpriteSheet* spriteSheet = new SpriteSheet(this, GET_MANAGER(ResourceManager)->GetSpriteSheet("Player"));
	
	spriteSheet->SetAnimation("idle");

	m_sprite = spriteSheet;

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, {100, 100});
	m_collider->SetGizmo(true);
	m_physicsCollision = true;

	m_pStateMachine = new StateMachine<Player>(this, State::Count);
	Action<Player>* pIdle = m_pStateMachine->CreateAction<PlayerAction_Idle>(State::idle);
	Action<Player>* pWalking = m_pStateMachine->CreateAction<PlayerAction_Walking>(State::walking);
	Action<Player>* pJumping = m_pStateMachine->CreateAction<PlayerAction_jumping>(State::jumping);
	Action<Player>* pParrying = m_pStateMachine->CreateAction<PlayerAction_Parrying>(State::parrying);
	Action<Player>* pAttacking = m_pStateMachine->CreateAction<PlayerAction_Shooting>(State::attacking);
	Action<Player>* pDash = m_pStateMachine->CreateAction<PlayerAction_Dash>(State::dash);
	Action<Player>* pFall = m_pStateMachine->CreateAction<PlayerAction_Falling>(State::falling);
	Action<Player>* pLand = m_pStateMachine->CreateAction<PlayerAction_Landing>(State::land);

    m_pStateMachine->SetState(State::idle);
}

void Player::OnCollision(Entity* other)
{
	if (!m_isAlive) return;
	if (other->IsTag(TestScene::Tag::platform)) {
		Platform* plat = dynamic_cast<Platform*>(other);
		Collider* collide = plat->GetCollider();
		collide->GetSide(m_collider, m_sideCollider);
	}
}

void Player::parry() {
	if (m_parryCooldown <= 0) {
		m_parryCooldown = 4.f;
		m_Parrying = true;
		std::cout << "going to parry !" << std::endl;
	}
}

void Player::Attack() {
	m_shootCooldown = 2.f;
	m_ammo -= 1;
	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), m_lastDir,this);
	bullet->SetMass(1);
	bullet->SetGravityDirection(sf::Vector2f(0, 1));

}

void Player::Jump()
{

	if (m_jumpCooldown <= 0 && m_jumpCount <= m_maxJumps) {
		std::cout << m_jumpCount;
		SetMass(100);
		SetGravityForce(-500);
		m_jumpCount += 1;
		m_jumpCooldown = 0.5f;
	}
}

void Player::Dash() {
	if (m_dashCooldown <= 0 && !m_dash) {
		m_dash = true;
		m_dashDuration = 0.3f;
		m_dashCooldown = 1.5f; 

		float dashSpeed = 1000.f;
		m_friction = 0.0f; 
		SetMass(0);
		SetGravityForce(0);
		if (m_lastDir.x != 0) {
			m_Direction.x = m_lastDir.x;
		}
		else {
			m_Direction.x = 1;
		}
		m_Speed = dashSpeed;
	}
}


const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case walking: return "walking";
	case idle: return "idle";
	case jumping: return "jumping";
	case parrying: return "parrying";
	case attacking: return "attacking";
	case dash: return "Dashing";
	case falling: return "falling";
	case land: return "landing";
	default: return "Unknown";
	}
}

void Player::TakeDamage(int damage) {
	m_life -= damage;
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
	m_realoadTime -= dt;
	if (m_dash) { m_dashDuration -= dt;}
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
		CheckState(State::walking);
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -PositiveJoystickSensibility) {
		inputX = -1.0f;
		m_lastDir = { -1,0 };
		CheckState(State::walking);
	}
	 if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || X) && !m_jumping) {
		CheckState(State::jumping);
	}
	 if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || R2) {
		if (m_parryCooldown <= 0)CheckState(State::attacking);
	}
	 if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		if (m_parryCooldown <= 0) m_life--;
	}
	 if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || L2) {
		if (m_shootCooldown <= 0) CheckState(State::parrying);
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || R1) {
		CheckState(State::dash);
	}
	 if (joystickX < PositiveJoystickSensibility && joystickX > -PositiveJoystickSensibility && !X && !L2 && !R2 && !R1 && m_state != land) {
		 CheckState(State::idle);
	 }
	bool reversing = (inputX != 0 && inputX != m_Direction.x);

		if (inputX != 0 && (!reversing || m_Speed < 100.0f)) {
			m_Direction.x = inputX;
			m_Speed += m_acceleration * dt;
		}
		else if (inputX == 0) {
			m_Speed -= m_friction * dt;
		}
		if (reversing && m_Speed > 0) {
			m_Speed -= turnResistance * dt;
			if (m_Speed < 0) m_Speed = 0;
		}

		if (m_Speed > MAX_SPEED && !m_dash) m_Speed = MAX_SPEED;
		if (m_Speed < 0) m_Speed = 0;
		X = false;
		R2 = false;
		L2 = false;
		R1 = false;
		joystickX = 0;
		joystickY = 0;
}

void Player::CheckPlayerStates()
{
	sf::Vector2f pos = GetPosition();
	float dt = GetDeltaTime();

	if (m_parryTime) m_parryTime -= dt;
	if (m_parryTime <= 0) {
		m_Parrying = false;
		m_parryTime = PARRY_DURATION;
	}
	if (m_life <= 0) {
		m_life = 0;
		m_isAlive = false;
	}
	if (m_realoadTime <= 0 && m_ammo < 3) {
		m_ammo += 1;
	}
	if (m_dashDuration <= 0) {
		m_dash = false;
		SetMass(100);
		m_friction = 400.f;
		m_dashDuration = 2.f;
	}
	if (pos.y >= 2100 && pos.x < 2300) {
		m_life -= 1;
		SetPosition(m_oldX -200, m_oldY);
		if (!m_sideCollider.down) SetPosition(pos.x - 200, m_oldY);
	}
}

bool Player::CheckState(State newState)
{
	if (mTransitions[(int)m_state][(int)newState])
	{
		m_state = newState;
		m_pStateMachine->SetState(m_state);

		return true;
	}

	return false;
}

void Player::PlayerMove()
{
	float dt = GetDeltaTime();
	sf::Vector2f pos = GetPosition();

	pos.x += m_Direction.x * m_Speed * dt;

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

	PlayerCheckCollision();
	DecreaseCD(dt);
	CheckPlayerStates();
	HandleInput();
	PlayerMove();
	m_pStateMachine->Update();
	const char* stateName = GetStateName((Player::State)m_pStateMachine->GetCurrentState());
	std::string life = std::to_string(m_life);
	Debug::DrawText(GetPosition().x, GetPosition().y - 175, stateName, 1.f, 1.f, sf::Color::Red);
	Debug::DrawText(GetPosition().x, GetPosition().y - 225, life, 0.5f, 0.5f, sf::Color::Red);
	ResetCollide();
}

void Player::OnAnimationEnd(const std::string& _animationIndex)
{
	if (_animationIndex == "jump")
	{
		CheckState(State::falling);
	}

	else if(_animationIndex == "land")
	{ 
		CheckState(State::idle);
	}
}
	

void Player::ResetCollide() {
	m_sideCollider.down = false;
	m_sideCollider.up = false;
	m_sideCollider.left = false;
	m_sideCollider.right = false;
}

void Player::PlayerCheckCollision() {
	if (m_sideCollider.up) {
		SetGravityForce(0);
	}
	if (m_sideCollider.down) {
		m_oldX = GetPosition().x;
		m_oldY = GetPosition().y;
		SetGravityForce(0);
		m_jumpCount = 0;
		m_jumping = false;
	}
	else if (!m_jumping && !m_sideCollider.down) {
		CheckState(State::falling);
	}
	if (m_sideCollider.left) {
		m_Speed = 0;
	}
	if (m_sideCollider.right) {
		m_Speed = 0;
	}
}
