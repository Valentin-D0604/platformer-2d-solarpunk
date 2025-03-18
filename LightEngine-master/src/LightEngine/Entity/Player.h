#pragma once
#include "PhysicsEntity.h"
#include "Bullet.h"
#include "../Utils/StateMachine.h"

#define MAX_SPEED 400
#define PARRY_DURATION 10.f


class Player : public PhysicsEntity
{
	//--------moving---------
	bool m_jumping = false;
	float m_oldY = 0;
	bool m_dash = true;
	//sf::Vector2f m_velocity;
	float m_acceleration = 600.0f;
	float m_friction = 400.0f;
	float turnResistance = 800.0f; 
	sf::Vector2f m_lastDir = { 1,0 };
	bool m_goingRight = false;
	bool m_goingLeft = false;
	//---------stats---------
	bool m_isAlive;
	int m_life = 3;
	int m_maxLife = 10;
	int m_ammo = 3;
	int m_maxAmmo = 10;
	//---------time--------
	float m_parryCooldown = 2.f;
	float m_shootCooldown = 2.f;
	float m_dashCooldown = 2.f;
	float m_dashDuration = 1.f;
	float m_jumpCooldown = 1.f;
	float m_parryTime = PARRY_DURATION;
	//-----------abilities--------
	bool m_Parrying = false;
	int m_jumpCount = 0;
	const int m_maxJumps = 2;

	StateMachine<Player>* m_pStateMachine;

	enum State
	{
		walking,
		jumping,
		parrying,
		attacking,
		idle,
		dash,

		Count
	};
	State m_state = State::idle;
	static constexpr int STATE_COUNT = static_cast<int>(State::Count);

	int mTransitions[STATE_COUNT][STATE_COUNT] =
	{
		// w,     j,      p ,    a,     d,     i,
		{  0,     1,      1,     1,     1,     1}, // walking
		{  1,     0,      1,     1,     1,     1}, // jumping
		{  1,     1,      0,     0,     1,     1}, // parrying
		{  1,     1,      0,     0,     1,     1}, // attacking
		{  0,     0,      0,     0,     0,     1},  // dash
		{  1,     1,      1,     1,     1,     0}  // idle
	};
public:
	void OnInitialize() override;
	void OnCollision(Entity* _other) override;
	void OnUpdate() override;
	
	const char* GetStateName(State _state) const;
	void parry();
	void Attack();
	void Jump();
	void Dash();
	void TakeDamage(int damage);
	void AddBuff(int bullet);
	void DecreaseCD(float time);
	void HandleInput();
	void CheckPlayerStates();
	void PlayerMove();
	bool IsAlive();
	bool IsParry();
protected:

	friend class PlayerAction_Walking;
	friend class PlayerAction_jumping;
	friend class PlayerAction_Shooting;
	friend class PlayerAction_Parrying;
	friend class PlayerAction_Idle;
	friend class PlayerAction_Dash;
};


