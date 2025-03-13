#pragma once
#include "PhysicsEntity.h"
#include "Bullet.h"
#include "StateMachine.h"

#define MAX_VELOCITY 400
#define PARRY_DURATION 5.f

class Player : public PhysicsEntity
{
	//--------moving---------
	bool m_jumping;
	float m_OldY = 0;
	sf::Vector2f m_velocity;
	float m_acceleration = 600.0f;
	float m_friction = 400.0f;
	float m_airResistance = 100.0f;
	sf::Vector2f m_lastDir = { 1,0 };
	bool m_goingRight = false;
	bool m_goingLeft = false;
	//---------stats---------
	bool m_isAlive = true;
	int m_life = 3;
	int m_ammo = 10;

	//---------time--------
	float m_parryCooldown = 2.f;
	float m_shootCooldown = 2.f;
	float m_dashCooldown = 2.f;
	float m_parryTime = PARRY_DURATION;
	//-----------abilities--------
	bool m_Parrying = false;

	StateMachine<Player>* mpStateMachine;

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
public:
	void OnInitialize() override;
	void onCollision(Entity* other) override;
	void OnUpdate() override;
	
	const char* GetStateName(State state) const;
	void parry();
	void Attack();
	void TakeDamage(int damage);
	void AddBullet(int bullet);
	void DecreaseCD(float time);
	void HandleInput();
	void CheckPlayerStates();
	void PlayerMove();
protected:
	friend class PlayerCondition_IsWalking;
	friend class PlayerCondition_IsJumping;
	friend class PlayerCondition_IsShooting;
	friend class PlayerCondition_IsParrying;
	friend class PlayerCondition_IsIdle;

	friend class PlayerAction_Walking;
	friend class PlayerAction_jumping;
	friend class PlayerAction_Shooting;
	friend class PlayerAction_Parrying;
	friend class PlayerAction_Idle;
	friend class PlayerAction_Dash;
};


