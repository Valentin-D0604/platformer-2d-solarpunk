#pragma once
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Mob1 : public PhysicsEntity
 {

	//---------stats---------
	bool m_IsAlive = true;
	int m_Life = 1;
	sf::Vector2f m_Velocity;
	float m_ShootCooldown = 2.f;
	float m_WalkingTimer = 3.f;
	//------------------------

	StateMachine<Mob1>* m_pStateMachine;

	enum State
	{
		walking,
		chasing,
		attacking,
		idle,

		Count
	};
public:
	void OnInitialize() override;
	void onCollision(Entity* _other) override;
	void OnUpdate() override;

	float GetDistanceToPlayer();
	void TakeDamage(int _damage);
private :
	friend class Mob1Action_Walking;
	friend class Mob1Action_Chasing;
	friend class Mob1Action_Attacking;
	friend class Mob1Action_Idle;
	
};

