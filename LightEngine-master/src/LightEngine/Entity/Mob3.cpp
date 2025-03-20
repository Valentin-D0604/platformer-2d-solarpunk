#include "../Entity/Mob3.h"

#include "../Actions/Mob3Action.h"
#include "../Conditions/Mob3Condition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/Sprite.h"
#include "../Entity/Collectable.h"
#include "../Entity/Platform.h"

#include "../Utils/Utils.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include "../Entity/Explode.h"
#include <iostream>

void Mob3::OnInitialize()
{
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Test")));
	m_sprite->setScale({ 0.25,0.25 });
	SetTag(TestScene::Tag::mob3);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, { 102,96 });
	m_pStateMachine = new StateMachine<Mob3>(this, State::Count);
	m_sprite->setScale({ 0.25,0.25 });
	m_collider->SetGizmo(true);
	m_Speed = 300;
	m_physicsCollision = true;
	//idle
	{
		Action<Mob3>* pIdle = m_pStateMachine->CreateAction<Mob3Action_Idle>(State::idle);
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
		Action<Mob3>* pWalking = m_pStateMachine->CreateAction<Mob3Action_Walking>(State::walking);
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
		Action<Mob3>* pChasing = m_pStateMachine->CreateAction<Mob3Action_Chasing>(State::chasing);
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
		Action<Mob3>* pAttacking = m_pStateMachine->CreateAction<Mob3Action_Attacking>(State::attacking);
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

	m_pStateMachine->SetState(State::idle);
}

void Mob3::OnCollision(Entity* _other)
{
	if (_other->IsTag(TestScene::Tag::mob3)) return;
	if (_other->IsTag(TestScene::Tag::platform)) {
		Platform* plat = dynamic_cast<Platform*>(_other);
		Collider* collide = plat->GetCollider();
		collide->GetSide(m_collider, m_sideCollider);
	}
}

void Mob3::OnUpdate()
{
	if (m_life <= 0) { Attack(); Destroy(); }

	m_pStateMachine->Update();
	Mob3CheckCollision();
}

void Mob3::OnDestroy()
{
	int rando = rand() % 2;
	if (rando == 0) return;
	Collectable* buff = CreateEntity<Collectable>();
	buff->InitCollec(GetPosition(), { 0,1 }, this);
	buff->SetMass(10);
	buff->SetGravityDirection(sf::Vector2f(0, 1));
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
				m_Speed = 200;
			}
			else {
				if (!player->IsParry()) player->TakeDamage(1);
				else (TakeDamage(1));
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

void Mob3::TakeDamage(int _damage) {
	m_life -= _damage;
	if (m_canExplode) {
		Attack();
	}
}

void Mob3::ResetCollide() {
	m_sideCollider.down = false;
	m_sideCollider.up = false;
	m_sideCollider.left = false;
	m_sideCollider.right = false;
}

void Mob3::Mob3CheckCollision() {
	if (m_sideCollider.up) {
		SetGravityForce(0);
	}
	if (m_sideCollider.down) {
			SetGravityForce(0);
			SetMass(0);
	}
	else {
		SetMass(100);
	}
	if (m_sideCollider.left) {
	}
	if (m_sideCollider.right) {
	}
}