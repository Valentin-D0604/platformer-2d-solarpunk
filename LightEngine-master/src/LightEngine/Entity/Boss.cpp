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
	std::vector<sf::Vector2f> idlePositions = { {89,304}, {91,300}, {99,294}, {108,289}, {113,287}, {115,287}, {113,291}, {105,294}, {99,300} };
	std::vector<sf::Vector2f> groundSmashPositions = { {169,271}, {168,254}, {170,203}, {172,170}, {173,157}, {174,161}, {174,166}, {172,179}, {181,227}, {175,289} };
	std::vector<sf::Vector2f> throwPositions = { {159,142}, {157,144}, {152,152}, {147,162}, {138,175}, {129,199}, {130,255}, {180,347}, {194,353}, {160,325}, {174,321}, {182,315}, {184,317}, {184,321}, {182,322}, {182,320}, {182,294}, {186,247}, {187,222} };
	std::vector<sf::Vector2f> retreatPositions = { {169,312}, {169,312}, {168,314}, {165,313}, {168,316}, {172,314}, {183,314}, {203,317}, {229,319}, {240,321} };
	std::vector<sf::Vector2f> RidlePositions = { {411,302}, {407,298}, {401,293}, {394,288}, {386,284}, {386,285}, {389,288}, {393,293}, {402,299} };
	std::vector<sf::Vector2f> RgroundSmashPositions = { {327,271}, {328,253}, {326,204}, {326,171}, {325,156}, {324,160}, {323,165}, {321,178}, {321,226}, {322,288} };
	std::vector<sf::Vector2f> RthrowPositions = { {293,346}, {296,343}, {299,339}, {305,330}, {318,313}, {334,295}, {348,271}, {336,215}, {331,206}, {336,299}, {317,314}, {314,318}, {314,321}, {314,322}, {314,324}, {316,321}, {316,296}, {315,246}, {314,221} };
	std::vector<sf::Vector2f> RretreatPositions = { {329,312}, {331,312}, {336,312}, {334,311}, {328,310}, {302,305}, {268,307}, {246,312}, {240,317}, {240,321} };
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));

	SetTag(TestScene::Tag::boss);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_position = pos;

	m_pStateMachine = new StateMachine<Boss>(this, count);

	m_left = GetScene()->CreateEntity<Hand>();
	m_left->PositionSettings(idlePositions, groundSmashPositions, throwPositions, retreatPositions);
	m_left->m_isLeft = true;


	m_right = GetScene()->CreateEntity<Hand>();
	m_right->PositionSettings(RidlePositions, RgroundSmashPositions, RthrowPositions, RretreatPositions);
	m_right->m_isLeft = false;

	m_left->SetOwner(this);
	m_right->SetOwner(this);

	if (m_left == nullptr || m_right == nullptr) {
		std::cout << "Erreur : Mains non allouées correctement !" << std::endl;
	}

	//IDLE
	{
		Action<Boss>* pIdle = m_pStateMachine->CreateAction<BossAction_Idle>(BossActionType::idle);
				
		{//smashing
			auto transition = pIdle->CreateTransition(BossActionType::groundSmash);
			auto condition = transition->AddCondition<BossCondition_IsGroundSmashing>();
		}
		
		{//throwing
			auto transition = pIdle->CreateTransition(BossActionType::throwRock);
			auto condition = transition->AddCondition<BossCondition_IsThrowing>();
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
	m_pStateMachine->SetState(BossActionType::idle);
}


void Boss::Update() {
	m_pStateMachine->Update();

	std::cout << "Boss State" << m_pStateMachine->GetCurrentState() << std::endl;
	
	if (m_isIdle)
	{
		m_timerforIdle += GetDeltaTime();
		if (m_timerforIdle >= 5.0f)
		{
			m_isIdle = false;
			m_timerforIdle = 0.0f;
		}
	}
	else if (m_isGroundSmashing)
	{
		m_timerforGroundSmash += GetDeltaTime();
		if (m_timerforGroundSmash >= 5.0f)
		{
			m_isGroundSmashing = false;
			m_timerforGroundSmash = 0.0f;
		}
	}
	else if (m_isThrowing)
	{
		m_timerforThrowing += GetDeltaTime();
		if (m_timerforThrowing >= 5.0f)
		{
			m_isThrowing = false;
			m_timerforThrowing = 0.0f;
		}
	}
	else if (m_GrabRock)
	{
		m_timerforGrabRock += GetDeltaTime();
		if (m_timerforGrabRock >= 5.0f)
		{
			m_GrabRock = false;
			m_timerforGrabRock = 0.0f;
		}
	}
	else if (m_isRetreating)
	{
		m_timerforRetreat += GetDeltaTime();
		if (m_timerforRetreat >= 5.0f)
		{
			m_isRetreating = false;
			m_timerforRetreat = 0.0f;
		}
	}


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
	switch (action) {
	case BossActionType::grabRock:
		break;

	case BossActionType::groundSmash:
		m_left->PerformGroundSmash();
		m_right->PerformGroundSmash();
		break;

	case BossActionType::throwRock:
		m_left->ThrowRock();
		break;

	case BossActionType::retreat:
		m_left->Stop();
		m_right->Stop();
		break;
	}
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