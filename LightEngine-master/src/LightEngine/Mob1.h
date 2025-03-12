#pragma once
#include "PhysicsEntity.h"
#include "StateMachine.h"

class Mob1 : public PhysicsEntity
 {

	//---------stats---------
	bool m_isAlive = true;
	int m_life = 3;
	sf::Vector2f m_velocity;
	float m_shootCooldown = 2.f;
	float m_walkingTimer = 3.f;
	//------------------------

	StateMachine<Mob1>* mpStateMachine;

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
	void onCollision(Entity* other) override;
	void OnUpdate() override;

	float GetDistanceToPlayer();
private :
	friend class Mob1Action_Walking;
	friend class Mob1Action_Chasing;
	friend class Mob1Action_Attacking;
	friend class Mob1Action_Idle;
	
};

