#pragma once

#include "Entity.h"
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
private:
    Hand* m_left;
	Hand* m_right;
    int m_hp;
	bool m_isGroundSmashing = false;
	bool m_isRetreating = false;
	bool m_GrabRock = false;
	bool m_isThrowing = false;
	bool m_isIdle = false;
	float m_timerforGroundSmash = 0.0f;
	float m_timerforThrowing = 0.0f;
	float m_timerforRetreat = 0.0f;
	float m_timerforIdle = 0.0f;
	float m_timerforGrabRock = 0.0f;

	sf::Vector2f m_position;
	
    StateMachine<Boss>* m_pStateMachine;

public:
    void OnInitialize() override;
    void Update() override;
    void StartAttack(BossActionType action);
	float GetDistanceToPlayer();

	bool IsGroundSmashing() { return m_isGroundSmashing;}
	bool IsRetreating() { return m_isRetreating; }
	bool IsGrabbingRock() { return m_GrabRock; }
	bool IsThrowing() {	return m_isThrowing; }

private:
	friend class BossAction_GrabRock;
	friend class BossAction_GroundSmash;
	friend class BossAction_Throwing;
	friend class BossAction_Retreat;
	friend class BossAction_Idle;
};

