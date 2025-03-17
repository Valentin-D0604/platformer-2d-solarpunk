#include "Boss.h"

#include "../Actions/BossAction.h"
#include "../Conditions/BossCondition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/Sprite.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Boss::OnInitialize()
{
	//IDLE
	{
		Action<Boss>* pIdle = mpStateMachine->CreateAction<BossAction_Idle>(BossActionType::IDLE);
		
		{//sweeping
			auto transition = pIdle->CreateTransition(BossActionType::SWEEP);
			auto condition = transition->AddCondition<BossCondition_IsSweeping>();
		}
		
		{//smashing
			auto transition = pIdle->CreateTransition(BossActionType::GROUND_SMASH);
			auto condition = transition->AddCondition<BossCondition_IsGroundSmashing>();
		}
		
		{//throwing
			auto transition = pIdle->CreateTransition(BossActionType::THROW_ROCK);
			auto condition = transition->AddCondition<BossCondition_IsThrowing>();
		}
	}
	
	//SWEEPING
	{
		Action<Boss>* pWalking = mpStateMachine->CreateAction<BossAction_Sweeping>(BossActionType::SWEEP);
		
		{//idle
			auto transition = pWalking->CreateTransition(BossActionType::IDLE);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//GROUND SMASH
	{
		Action<Boss>* pChasing = mpStateMachine->CreateAction<BossAction_GroundSmash>(BossActionType::GROUND_SMASH);
		
		{//idle
			auto transition = pChasing->CreateTransition(BossActionType::IDLE);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//TRHOWING
	{
		Action<Boss>* pAttacking = mpStateMachine->CreateAction<BossAction_Throwing>(BossActionType::THROW_ROCK);
		
		{//idle
			auto transition = pAttacking->CreateTransition(BossActionType::IDLE);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	mpStateMachine->SetState(BossActionType::IDLE);
}


void Boss::Update() {
	mpStateMachine->Update();
}

void Boss::StartAttack(BossActionType action) {
	if (m_isStunned) return; // Pas d'attaque si stun

	switch (action) {
	case BossActionType::SWEEP:
		m_left->PerformSweep();
		m_right->PerformSweep();
		break;

	case BossActionType::GROUND_SMASH:
		m_left->PerformGroundSmash();
		m_right->PerformGroundSmash();
		break;

	case BossActionType::THROW_ROCK:
		m_left->ThrowRock();
		break;

	case BossActionType::STUNNED:
		Stun();
		break;
	}
}

void Boss::Stun() {
	m_isStunned = true;
	m_left->Stun();
	m_right->Stun();
	m_left->SetVulnerable(true);
	m_right->SetVulnerable(true);
	RemoveArmor();
}

void Boss::RemoveArmor() {
	m_hp = 48;
	m_left->RemoveArmor();
	m_right->RemoveArmor();
}

float Boss::GetDistanceToPlayer()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();
	float distance = GetPosition().Distance(player->GetPosition());
	return distance;
}

bool Boss::IsStunned()
{
	if (m_isStunned != 1 && m_isStunned != 0) {
		return false;
	}
	return m_isStunned;
}

bool Boss::IsSweepping()
{
	if (m_isSweeping != 1 && m_isSweeping != 0) {
		return true;
	}
	return m_isSweeping;
}

bool Boss::IsGroundSmashing()
{
	if (m_isGroundSmashing != 1 &&  m_isGroundSmashing != 0) {
		return true;
	}
	return m_isGroundSmashing;
}

bool Boss::IsThrowing()
{
	if (m_isThrowing != 1 && m_isThrowing != 0) {
		return true;
	}
	return m_isThrowing;
}
