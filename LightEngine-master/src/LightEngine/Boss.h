#pragma once

#include "PhysicsEntity.h"
#include "StateMachine.h"

class Boss : public PhysicsEntity
{
	//---------stats---------
	bool m_isAlive = true;
	int m_life = 20;
	sf::Vector2f m_velocity;
	float m_shootCooldown = 2.f;
	float m_walkingTimer = 3.f;
	bool m_isVulnerable = false;
	//------------------------

	StateMachine<Boss>* mpStateMachine;

	enum State
	{
		rushing,
		smashing,
		throwing,
		idle,

		Count
	};

public:
	void OnInitialize() override;
	void onCollision(Entity* other) override;
	void OnUpdate() override;

	float GetDistanceToPlayer();
	void TakeDamage(int damage);
	void MoveSideToSide(float speed);
	void SetVulnerable(bool isVulnerable) { m_isVulnerable = isVulnerable; }

private:
	friend class BossAction_Sweeping;
	friend class BossAction_GroundSmash;
	friend class BossAction_Throwing;
	friend class BossAction_Stunned;
	friend class BossAction_Idle;
};

