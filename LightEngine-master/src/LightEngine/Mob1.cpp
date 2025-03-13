#include "Mob1.h"

#include "Mob1Action.h"
#include "Mob1Condition.h"
#include "RectangleCollider.h"

#include "TestScene.h"
#include "Player.h"

#include "Debug.h"

#include <iostream>

void Mob1::OnInitialize()
{

	SetTag(TestScene::Tag::mob1);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, {10,10});
	mpStateMachine = new StateMachine<Mob1>(this, State::Count);

	//idle
	{
		Action<Mob1>* pIdle = mpStateMachine->CreateAction<Mob1Action_Idle>(State::idle);
		{//walking
			auto transition = pIdle->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob1Condition_IsWalking>();
		}
		{//chasing
			auto transition = pIdle->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob1Condition_IsChasing>();
		}
		{//attacking
			auto transition = pIdle->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob1Condition_IsAttacking>();
		}

	}
	//walking
	{
		Action<Mob1>* pWalking = mpStateMachine->CreateAction<Mob1Action_Walking>(State::walking);
		{//walking
			auto transition = pWalking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob1Condition_IsIdle>();
		}
		{//chasing
			auto transition = pWalking->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob1Condition_IsChasing>();
		}
		{//attacking
			auto transition = pWalking->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob1Condition_IsAttacking>();
		}

	}

	//chasing
	{
		Action<Mob1>* pChasing = mpStateMachine->CreateAction<Mob1Action_Chasing>(State::chasing);
		{//walking
			auto transition = pChasing->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob1Condition_IsWalking>();
		}
		{//chasing
			auto transition = pChasing->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob1Condition_IsIdle>();
		}
		{//attacking
			auto transition = pChasing->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob1Condition_IsAttacking>();
		}
	}

	//attacking
	{
		Action<Mob1>* pAttacking = mpStateMachine->CreateAction<Mob1Action_Attacking>(State::attacking);
		{//walking
			auto transition = pAttacking->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob1Condition_IsWalking>();
		}
		{//chasing
			auto transition = pAttacking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob1Condition_IsIdle>();
		}
		{//attacking
			auto transition = pAttacking->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob1Condition_IsChasing>();
		}
	}

	mpStateMachine->SetState(State::idle);
}

void Mob1::onCollision(Entity* other)
{
	if (other->IsTag(TestScene::Tag::mob1)) return;
}

void Mob1::OnUpdate()
{
	if (m_life <= 0) { Destroy(); }

	mpStateMachine->Update();
}

float Mob1::GetDistanceToPlayer()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();

	sf::Vector2f playerPos = player->GetPosition(); // Fonction qui récupère la position du joueur
	sf::Vector2f mobPos = GetPosition();
	return sqrt(pow(playerPos.x - mobPos.x, 2) + pow(playerPos.y - mobPos.y, 2));
}

void Mob1::TakeDamage(int damage) {
	m_life -= damage;
}