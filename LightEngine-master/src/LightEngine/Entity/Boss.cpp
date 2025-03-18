#include "Boss.h"
#include "Player.h"

#include "../Actions/BossAction.h"
#include "../Conditions/BossCondition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"

#include "../Graphics/Sprite.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Boss::OnInitialize()
{
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));

	SetTag(TestScene::Tag::boss);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_pStateMachine = new StateMachine<Boss>(this, count);

	m_left = GetScene()->CreateEntity<Hand>();
	m_left->m_isLeft = true;

	m_right = GetScene()->CreateEntity<Hand>();
	m_right->m_isLeft = false;

	m_left->SetOwner(this);
	m_right->SetOwner(this);

	if (m_left == nullptr || m_right == nullptr) {
		std::cout << "Erreur : Mains non allouées correctement !" << std::endl;
	}

	//IDLE
	{
		Action<Boss>* pIdle = m_pStateMachine->CreateAction<BossAction_Idle>(BossActionType::idle);
		
		{//sweeping
			auto transition = pIdle->CreateTransition(BossActionType::sweep);
			auto condition = transition->AddCondition<BossCondition_IsSweeping>();
		}
		
		{//smashing
			auto transition = pIdle->CreateTransition(BossActionType::groundSmash);
			auto condition = transition->AddCondition<BossCondition_IsGroundSmashing>();
		}
		
		{//throwing
			auto transition = pIdle->CreateTransition(BossActionType::throwRock);
			auto condition = transition->AddCondition<BossCondition_IsThrowing>();
		}
	}
	
	//SWEEPING
	{
		Action<Boss>* pWalking = m_pStateMachine->CreateAction<BossAction_Sweeping>(BossActionType::sweep);
		
		{//idle
			auto transition = pWalking->CreateTransition(BossActionType::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//GROUND SMASH
	{
		Action<Boss>* pChasing = m_pStateMachine->CreateAction<BossAction_GroundSmash>(BossActionType::groundSmash);
		
		{//idle
			auto transition = pChasing->CreateTransition(BossActionType::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//TRHOWING
	{
		Action<Boss>* pAttacking = m_pStateMachine->CreateAction<BossAction_Throwing>(BossActionType::throwRock);
		
		{//idle
			auto transition = pAttacking->CreateTransition(BossActionType::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//STUNNED
	{
		Action<Boss>* pStunned = m_pStateMachine->CreateAction<BossAction_Stunned>(BossActionType::stunned);

		{//idle
			auto transition = pStunned->CreateTransition(BossActionType::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	m_pStateMachine->SetState(BossActionType::idle);
}


void Boss::Update() {
	m_pStateMachine->Update();
	
	if (m_left != nullptr) {
		m_left->OnUpdate();
	}
	else {
		std::cout << " main gauche nullptr " << std::endl;
	}

	if (m_right != nullptr)
	{
		m_right->OnUpdate();
	}
	else
	{
		std::cout << " main droite nullptr " << std::endl;
	}
}

void Boss::StartAttack(BossActionType action) {
	if (m_isStunned) return; // Pas d'attaque si stun

	switch (action) {
	case BossActionType::sweep:
		m_left->PerformSweep();
		m_right->PerformSweep();
		break;

	case BossActionType::groundSmash:
		m_left->PerformGroundSmash();
		m_right->PerformGroundSmash();
		break;

	case BossActionType::throwRock:
		m_left->ThrowRock();
		break;

	case BossActionType::stunned:
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
	if (player != nullptr && player->IsAlive()) {
		sf::Vector2f playerPos = player->GetPosition();
		sf::Vector2f mobPos = GetPosition();
		return sqrt(pow(playerPos.x - mobPos.x, 2) + pow(playerPos.y - mobPos.y, 2));
	}
	else return 10000;
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
