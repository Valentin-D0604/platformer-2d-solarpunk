#pragma once
#include "PhysicsEntity.h"
#include "StateMachine.h"

class Mob1 : public PhysicsEntity
{
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

};

