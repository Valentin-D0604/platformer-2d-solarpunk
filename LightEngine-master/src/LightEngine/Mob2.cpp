#include "Mob2.h"

#include "Mob2Action.h"
#include "Mob2Condition.h"
#include "RectangleCollider.h"

#include "TestScene.h"
#include "Player.h"
#include "Sprite.h"

#include "Utils/Utils.h"

#include "Debug.h"
#include "Managers.h"
#include <iostream>

void Mob2::OnInitialize()
{
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));
	m_sprite->setScale({ 0.25,0.25 });
	SetTag(TestScene::Tag::mob2);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, { 10,10 });
	mpStateMachine = new StateMachine<Mob2>(this, State::Count);

	//idle
	{
		Action<Mob2>* pIdle = mpStateMachine->CreateAction<Mob2Action_Idle>(State::idle);
		{//walking
			auto transition = pIdle->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob2Condition_IsWalking>();
		}
		{//chasing
			auto transition = pIdle->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob2Condition_IsChasing>();
		}
		{//attacking
			auto transition = pIdle->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob2Condition_IsAttacking>();
		}

	}
	//walking
	{
		Action<Mob2>* pWalking = mpStateMachine->CreateAction<Mob2Action_Walking>(State::walking);
		{//walking
			auto transition = pWalking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob2Condition_IsIdle>();
		}
		{//chasing
			auto transition = pWalking->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob2Condition_IsChasing>();
		}
		{//attacking
			auto transition = pWalking->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob2Condition_IsAttacking>();
		}

	}

	//chasing
	{
		Action<Mob2>* pChasing = mpStateMachine->CreateAction<Mob2Action_Chasing>(State::chasing);
		{//walking
			auto transition = pChasing->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob2Condition_IsWalking>();
		}
		{//chasing
			auto transition = pChasing->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob2Condition_IsIdle>();
		}
		{//attacking
			auto transition = pChasing->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob2Condition_IsAttacking>();
		}
	}

	//attacking
	{
		Action<Mob2>* pAttacking = mpStateMachine->CreateAction<Mob2Action_Attacking>(State::attacking);
		{//walking
			auto transition = pAttacking->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob2Condition_IsWalking>();
		}
		{//chasing
			auto transition = pAttacking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob2Condition_IsIdle>();
		}
		{//attacking
			auto transition = pAttacking->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob2Condition_IsChasing>();
		}
	}

	mpStateMachine->SetState(State::idle);
}

void Mob2::onCollision(Entity* other)
{
	if (other->IsTag(TestScene::Tag::mob2)) return;
}

void Mob2::OnUpdate()
{
	if (m_life <= 0) { Destroy(); }

	mpStateMachine->Update();
}

void Mob2::OnDestroy()
{
	int rando = rand() % 2;
	if (rando == 0) return;
	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), {0,1}, this, true);
	bullet->setMass(10);
	bullet->setGravityDirection(sf::Vector2f(0, 1));
}

void Mob2::Attack()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();
	if (player == nullptr) return;
	m_shootCooldown = 2.f;
	sf::Vector2f dir = player->GetPosition() - GetPosition();
	Utils::Normalize(dir);

	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), dir, this, false);
	bullet->setMass(1);
	bullet->setGravityDirection(sf::Vector2f(0, 1));
}

float Mob2::GetDistanceToPlayer()
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

void Mob2::TakeDamage(int damage) {
	m_life -= damage;
}