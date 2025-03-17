#pragma once

#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Sprite;
class RectangleCollider;

class Boss : public PhysicsEntity
{
	//---------stats---------
	bool m_isAlive = true;
	int m_life = 48;
	sf::Vector2f m_velocity;
	float m_shootCooldown = 2.f;
	float m_walkingTimer = 3.f;
	bool m_isVulnerable = false;
	float m_stunnedTimer = 3.f;
	Sprite* m_sprite;
	RectangleCollider* m_collider;
	
	//------------------------

	StateMachine<Boss>* mpStateMachine;

	enum State
	{
		idle,
		rushing,
		smashing,
		throwing,
		stunned,
		transition,
		movement,

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
	void SetState(State state) { mpStateMachine->SetState(state); }
	void SetAnimation(const std::string& name);
	void PerformGroundSlam();
	void ThrowProjectiles();
	void RemoveArmor();

private:
	friend class BossAction_Sweeping;
	friend class BossAction_GroundSmash;
	friend class BossAction_Throwing;
	friend class BossAction_Stunned;
	friend class BossAction_Moving;
	friend class BossAction_Transition;
	friend class BossAction_Idle;
};

