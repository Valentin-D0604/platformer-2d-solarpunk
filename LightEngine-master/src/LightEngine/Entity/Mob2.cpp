#include "../Entity/Mob2.h"

#include "../Actions/Mob2Action.h"
#include "../Conditions/Mob2Condition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/Sprite.h"
#include "../Entity/Collectable.h"

#include "../Utils/Utils.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>

void Mob2::OnInitialize()
{
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Test")));
	m_sprite->setScale({ 0.25,0.25 });
	SetTag(TestScene::Tag::mob2);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, { 10,10 });
	m_pStateMachine = new StateMachine<Mob2>(this, State::Count);
	m_collider->SetGizmo(true);
	//idle
	{
		Action<Mob2>* pIdle = m_pStateMachine->CreateAction<Mob2Action_Idle>(State::idle);
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
		Action<Mob2>* pWalking = m_pStateMachine->CreateAction<Mob2Action_Walking>(State::walking);
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
		Action<Mob2>* pChasing = m_pStateMachine->CreateAction<Mob2Action_Chasing>(State::chasing);
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
		Action<Mob2>* pAttacking = m_pStateMachine->CreateAction<Mob2Action_Attacking>(State::attacking);
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

	m_pStateMachine->SetState(State::idle);
}

void Mob2::OnCollision(Entity* _other)
{
	if (_other->IsTag(TestScene::Tag::mob2)) return;
}

void Mob2::OnUpdate()
{
	if (m_life <= 0) { Destroy(); }

	m_pStateMachine->Update();
}

void Mob2::OnDestroy()
{
	int rando = rand() % 2;
	if (rando == 0) return;
	Collectable* buff = CreateEntity<Collectable>();
	buff->InitCollec(GetPosition(), { 0,1 }, this);
	buff->SetMass(10);
	buff->SetGravityDirection(sf::Vector2f(0, 1));
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
	bullet->InitBullet(GetPosition(), dir, this);
	bullet->SetMass(1);
	bullet->SetGravityDirection(sf::Vector2f(0, 1));
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

void Mob2::TakeDamage(int _damage) {
	m_life -= _damage;
	std::cout << m_life;
}