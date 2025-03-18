#include "../Entity/Mob1.h"

#include "../Actions/Mob1Action.h"
#include "../Conditions/Mob1Condition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/Sprite.h"
#include "../Entity/Collectable.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Mob1::OnInitialize()
{
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Test")));

	SetTag(TestScene::Tag::mob1);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, {10,10});
	m_pStateMachine = new StateMachine<Mob1>(this, State::Count);

	//idle
	{
		Action<Mob1>* pIdle = m_pStateMachine->CreateAction<Mob1Action_Idle>(State::idle);
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
		Action<Mob1>* pWalking = m_pStateMachine->CreateAction<Mob1Action_Walking>(State::walking);
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
		Action<Mob1>* pChasing = m_pStateMachine->CreateAction<Mob1Action_Chasing>(State::chasing);
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
		Action<Mob1>* pAttacking = m_pStateMachine->CreateAction<Mob1Action_Attacking>(State::attacking);
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

	m_pStateMachine->SetState(State::idle);
}

void Mob1::OnCollision(Entity* _other)
{
	if (_other->IsTag(TestScene::Tag::mob1)) return;
}

void Mob1::OnUpdate()
{
	if (m_Life <= 0) { Destroy(); }

	m_pStateMachine->Update();
}

void Mob1::OnDestroy()
{
	int rando = rand() % 2;
	if (rando == 0) return;
	Collectable* buff = CreateEntity<Collectable>();
	buff->InitCollec(GetPosition(), { 0,1 }, this);
	buff->SetMass(10);
	buff->SetGravityDirection(sf::Vector2f(0, 1));
}

float Mob1::GetDistanceToPlayer()
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

void Mob1::TakeDamage(int damage) {
	m_Life -= damage;
}

void Mob1::Attack()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();
	if (player == nullptr) return;
	player->TakeDamage(1);
	GoToPosition(GetPosition().x+m_Direction.x, GetPosition().y + m_Direction.y,200);
	m_shootCooldown = 2.f;
}

