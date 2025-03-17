#pragma once

#include "Entity.h"
#include "../Utils/StateMachine.h"
#include "Hands.h"

class Sprite;
class RectangleCollider;
class Hand;

enum BossActionType {
	IDLE,
    SWEEP, 
    GROUND_SMASH, 
    THROW_ROCK,
    STUNNED,

	COUNT
};

class Boss : public Entity {
private:
    Hand* m_left;
	Hand* m_right;
    int m_hp;
    bool m_isStunned = false;
	bool m_isGroundSmashing = false;
	bool m_isThrowing = false;
	bool m_isSweeping = false;
	
    StateMachine<Boss>* mpStateMachine;

public:
    void OnInitialize() override;
    void Update() override;
    void StartAttack(BossActionType action);
    void Stun();
    void RemoveArmor();
	float GetDistanceToPlayer();

	bool IsStunned();
	bool IsSweepping();
	bool IsGroundSmashing();
	bool IsThrowing();


private:
	friend class BossAction_Sweeping;
	friend class BossAction_GroundSmash;
	friend class BossAction_Throwing;
	friend class BossAction_Stunned;
	friend class BossAction_Idle;
};

