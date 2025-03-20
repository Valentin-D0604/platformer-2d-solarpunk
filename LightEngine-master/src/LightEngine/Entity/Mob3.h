#pragma once
#include "../Entity/PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Mob3 : public PhysicsEntity
{

	//---------stats---------
	bool m_isAlive = true;
	int m_life = 3;
	bool m_canExplode = true;
	sf::Vector2f m_velocity;
	float m_shootCooldown = 2.f;
	float m_walkingTimer = 3.f;
	//------------------------

	StateMachine<Mob3>* m_pStateMachine;
	Side m_sideCollider;
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

	void ResetCollide();
	void Mob3CheckCollision();

	void Attack();
	float GetDistanceToPlayer();
	void TakeDamage(int damage);
private:
	friend class Mob3Action_Walking;
	friend class Mob3Action_Chasing;
	friend class Mob3Action_Attacking;
	friend class Mob2Action_Idle;

};

