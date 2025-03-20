#pragma once

#include "Entity.h"
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"
#include "Hands.h"

class Sprite;
class RectangleCollider;
class Hand;

enum BossActionType {

	idle,
	groundSmash, 
    throwRock,
	grabRock,
	retreat,

	count
};

class Boss : public Entity {

	static constexpr int STATE_COUNT = static_cast<int>(BossActionType::count);
	BossActionType m_state = BossActionType::idle;
	int mTransitions[STATE_COUNT][STATE_COUNT] =
	{
		// I,     G,      T , grab,     R
		{  0,     1,      0,     1,     0}, // idle
		{  1,     0,      0,     0,     0}, // groundSmash
		{  0,     0,      0,     0,     1}, // throwRock
		{  0,     0,      1,     0,     0}, // grabRock
		{  1,     0,      0,     0,     0}, // retreat
	};
private:
    Hand* m_left;
	Hand* m_right;
    int m_hp;
	float m_timerforIdle = 0.0f;
	BossActionType m_currentAction;
	sf::Vector2f m_position;
	
    StateMachine<Boss>* m_pStateMachine;

public:
    void OnInitialize() override;
    void Update() override;
	void TakeDamage(int _damage);
	BossActionType GetCurrentAction();
    void StartAttack(BossActionType action);
	float GetDistanceToPlayer();

	bool CheckState(BossActionType newState);

	bool m_isGroundSmashing = false;
	bool m_isRetreating = false;
	bool m_GrabRock = false;
	bool m_isThrowing = false;
	bool m_isIdle = false;

private:
	friend class BossAction_GrabRock;
	friend class BossAction_GroundSmash;
	friend class BossAction_Throwing;
	friend class BossAction_Retreat;
	friend class BossAction_Idle;
};

