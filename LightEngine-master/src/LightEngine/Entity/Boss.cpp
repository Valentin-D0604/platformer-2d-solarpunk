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
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	SetTag(TestScene::Tag::boss);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_collider = new RectangleCollider(pos, { 10,10 });
	mpStateMachine = new StateMachine<Boss>(this, State::Count);

	//IDLE
	{
		Action<Boss>* pIdle = mpStateMachine->CreateAction<BossAction_Idle>(State::idle);
		{//rushing
			auto transition = pIdle->CreateTransition(State::rushing);
			auto condition = transition->AddCondition<BossCondition_IsSweeping>();
		}
		{//smashing
			auto transition = pIdle->CreateTransition(State::smashing);
			auto condition = transition->AddCondition<BossCondition_IsGroundSmashing>();
		}
		{//throwing
			auto transition = pIdle->CreateTransition(State::throwing);
			auto condition = transition->AddCondition<BossCondition_IsThrowing>();
		}
	}
	
	//SWEEPING
	{
		Action<Boss>* pWalking = mpStateMachine->CreateAction<BossAction_Sweeping>(State::rushing);
		{//idle
			auto transition = pWalking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//GROUND SMASH
	{
		Action<Boss>* pChasing = mpStateMachine->CreateAction<BossAction_GroundSmash>(State::smashing);
		
		{//idle
			auto transition = pChasing->CreateTransition(State::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	//TRHOWING
	{
		Action<Boss>* pAttacking = mpStateMachine->CreateAction<BossAction_Throwing>(State::throwing);
		
		{//idle
			auto transition = pAttacking->CreateTransition(State::idle);
			auto condition = transition->AddCondition<BossCondition_IsIdle>();
		}
	}

	mpStateMachine->SetState(State::idle);
}

void Boss::onCollision(Entity* other)
{
	if (other->IsTag(TestScene::Tag::boss)) return;
}

void Boss::OnUpdate()
{

	if (m_life <= 0) { Destroy(); }

	if (m_isVulnerable == true)
	{
		m_stunnedTimer -= GetDeltaTime();
		if (m_stunnedTimer <= 0)
		{
			mpStateMachine->SetState(State::idle);
			m_stunnedTimer = 3.f;
		}
	}

	mpStateMachine->Update();
}

float Boss::GetDistanceToPlayer()
{
	TestScene* scene = dynamic_cast<TestScene*>(GetScene());
	Player* player = scene->GetPlayer();

	sf::Vector2f playerPos = player->GetPosition(); // Fonction qui récupère la position du joueur
	sf::Vector2f mobPos = GetPosition();
	return sqrt(pow(playerPos.x - mobPos.x, 2) + pow(playerPos.y - mobPos.y, 2));
}

void Boss::TakeDamage(int damage) {
	m_life -= damage;
}

void Boss::MoveSideToSide(float speed) {
	static bool movingRight = true;
	if (movingRight) {
		m_velocity.x = speed;
		if (GetPosition().x > 800) { // Assuming 800 is the right boundary
			movingRight = false;
		}
	}
	else {
		m_velocity.x = -speed;
		if (GetPosition().x < 0) { // Assuming 0 is the left boundary
			movingRight = true;
		}
	}
	SetPosition(GetPosition().x + m_velocity.x * GetDeltaTime(), GetPosition().y);
}

void Boss::SetAnimation(const std::string& name)
{
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture(name)));
}
