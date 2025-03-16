#include "Mob3.h"

#include "Mob3Action.h"
#include "Mob3Condition.h"
#include "RectangleCollider.h"

#include "TestScene.h"
#include "Player.h"
#include "Sprite.h"

#include "Utils/Utils.h"

#include "Debug.h"
#include "Managers.h"
#include "Explode.h"
#include <iostream>

void Mob3::OnInitialize()
{
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));
	m_sprite->setScale({ 0.25,0.25 });
	SetTag(TestScene::Tag::mob3);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, { 10,10 });
	mpStateMachine = new StateMachine<Mob3>(this, State::Count);
	m_sprite->setScale({ 0.25,0.25 });
	mSpeed = 300;
	//idle
	{
		Action<Mob3>* pIdle = mpStateMachine->CreateAction<Mob3Action_Idle>(State::idle);
		{//walking
			auto transition = pIdle->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob3Condition_IsWalking>();
		}
		{//chasing
			auto transition = pIdle->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob3Condition_IsChasing>();
		}
		{//attacking
			auto transition = pIdle->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob3Condition_IsAttacking>();
		}

	}
	//walking
	{
		Action<Mob3>* pWalking = mpStateMachine->CreateAction<Mob3Action_Walking>(State::walking);
		{//walking
			auto transition = pWalking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob3Condition_IsIdle>();
		}
		{//chasing
			auto transition = pWalking->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob3Condition_IsChasing>();
		}
		{//attacking
			auto transition = pWalking->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob3Condition_IsAttacking>();
		}

	}

	//chasing
	{
		Action<Mob3>* pChasing = mpStateMachine->CreateAction<Mob3Action_Chasing>(State::chasing);
		{//walking
			auto transition = pChasing->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob3Condition_IsWalking>();
		}
		{//chasing
			auto transition = pChasing->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob3Condition_IsIdle>();
		}
		{//attacking
			auto transition = pChasing->CreateTransition(State::attacking);
			auto condition = transition->AddCondition<Mob3Condition_IsAttacking>();
		}
	}

	//attacking
	{
		Action<Mob3>* pAttacking = mpStateMachine->CreateAction<Mob3Action_Attacking>(State::attacking);
		{//walking
			auto transition = pAttacking->CreateTransition(State::walking);
			auto condition = transition->AddCondition<Mob3Condition_IsWalking>();
		}
		{//chasing
			auto transition = pAttacking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<Mob3Condition_IsIdle>();
		}
		{//attacking
			auto transition = pAttacking->CreateTransition(State::chasing);
			auto condition = transition->AddCondition<Mob3Condition_IsChasing>();
		}
	}

	mpStateMachine->SetState(State::idle);
}

void Mob3::onCollision(Entity* other)
{
	if (other->IsTag(TestScene::Tag::mob2)) return;
}

void Mob3::OnUpdate()
{
	if (m_life <= 0) { Attack(); Destroy(); }

	mpStateMachine->Update();
}

void Mob3::OnDestroy()
{
	int rando = rand() % 2;
	if (rando == 0) return;
	Bullet* bullet = CreateEntity<Bullet>();
	bullet->InitBullet(GetPosition(), { 0,1 }, this, true);
	bullet->setMass(10);
	bullet->setGravityDirection(sf::Vector2f(0, 1));
}

void Mob3::Attack()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();
	if (player == nullptr) return;
	m_shootCooldown -= GetDeltaTime();
	sf::Vector2f dir = player->GetPosition() - GetPosition();
	Utils::Normalize(dir);

		if (m_shootCooldown <= 0) {
			m_shootCooldown = 2.f;
			if (m_canExplode) {
				Explode* damage = CreateEntity<Explode>();
				damage->SetPosition(GetPosition().x, GetPosition().y, 0.75, 0.75);
				m_canExplode = false;
				mSpeed = 200;
			}
			else {
				if (!player->IsParry()) player->TakeDamage(1);
			}
		}
}

float Mob3::GetDistanceToPlayer()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();
	if (player != nullptr && player->IsAlive()) {
		sf::Vector2f playerPos = player->GetPosition();
		sf::Vector2f mobPos = GetPosition();
		return sqrt(pow(playerPos.x - mobPos.x, 2) + pow(playerPos.y - mobPos.y, 2));
	}

	 return 10000;
}

void Mob3::TakeDamage(int damage) {
	m_life -= damage;
	if (m_canExplode) {
		Attack();
	}
}