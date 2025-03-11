#pragma once
#include "PhysicsEntity.h"
#include "Parry.h"
#include "StateMachine.h"
#define MAX_VELOCITY 400

class Player : public PhysicsEntity
{
	bool m_jumping;
	float m_OldY = 0;
	sf::Vector2f m_velocity; 
	float m_acceleration = 600.0f;
	float m_friction = 400.0f; 
	float m_airResistance = 100.0f; 
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
	void onCollision(Entity* other) override;
	void OnUpdate() override;

	const char* GetStateName(State state) const;
	void parry();

protected:
	friend class PlayerCondition_IsWalking;
	friend class PlayerCondition_IsJumping;
	friend class PlayerCondition_IsShooting;
	friend class PlayerCondition_IsParrying;
	friend class PlayerCondition_IsIdle;
};


