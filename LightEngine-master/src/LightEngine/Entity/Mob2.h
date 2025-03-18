#pragma once
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Mob2 : public PhysicsEntity
{

	//---------stats---------
	bool m_isAlive = true;
	int m_life = 2;
	sf::Vector2f m_velocity;
	float m_shootCooldown = 2.f;
	float m_walkingTimer = 3.f;
	//------------------------

	StateMachine<Mob2>* m_pStateMachine;

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
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
	void OnDestroy() override;

	void Attack();
	float GetDistanceToPlayer();
	void TakeDamage(int damage);
private:
	friend class Mob2Action_Walking;
	friend class Mob2Action_Chasing;
	friend class Mob2Action_Attacking;
	friend class Mob2Action_Idle;

};

