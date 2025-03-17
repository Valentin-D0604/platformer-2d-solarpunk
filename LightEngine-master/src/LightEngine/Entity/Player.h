#pragma once
#include "PhysicsEntity.h"
#include "Bullet.h"
#include "../Utils/StateMachine.h"

#define MAX_VELOCITY 400
#define PARRY_DURATION 5.f

class Player : public PhysicsEntity
{
	//--------moving---------
	bool m_Jumping;
	float m_OldY = 0;
	sf::Vector2f m_Velocity;
	float m_Acceleration = 600.0f;
	float m_Friction = 400.0f;
	float m_AirResistance = 100.0f;
	sf::Vector2f m_LastDir = { 1,0 };
	bool m_GoingRight = false;
	bool m_GoingLeft = false;
	//---------stats---------
	bool m_IsAlive = true;
	int m_Life = 3;
	int m_Ammo = 1;

	//---------time--------
	float m_ParryCooldown = 2.f;
	float m_ShootCooldown = 2.f;
	float m_DashCooldown = 2.f;
	float m_ParryTime = PARRY_DURATION;
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

		Count
	};
public:
	void OnInitialize() override;
	void onCollision(Entity* _other) override;
	void OnUpdate() override;
	
	const char* GetStateName(State _state) const;
	void parry();
	void Attack();
	void TakeDamage(int _damage);
	void AddBullet(int _bullet);
	void DecreaseCD(float _time);
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
};


