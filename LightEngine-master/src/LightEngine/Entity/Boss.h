#pragma once

#include "Entity.h"
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"
#include "Hands.h"

class Sprite;
class RectangleCollider;
class Hand;

enum BossActionType {

	idle,
	groundSmash, 
    throwRock,
	grabRock,
	retreat,

	count
};

class Boss : public Entity {

	static constexpr int STATE_COUNT = static_cast<int>(BossActionType::count);
	BossActionType m_state = BossActionType::idle;
	int mTransitions[STATE_COUNT][STATE_COUNT] =
	{
		// I,     G,      T , grab,     R
		{  0,     1,      0,     1,     0}, // idle
		{  1,     0,      0,     0,     0}, // groundSmash
		{  0,     0,      0,     0,     1}, // throwRock
		{  0,     0,      1,     0,     0}, // grabRock
		{  1,     0,      0,     0,     0}, // retreat
	};
private:
	bool createHands = false;
    Hand* m_left;
	Hand* m_right;
    int m_hp;
	float m_timerforIdle = 0.0f;
	BossActionType m_currentAction;
	sf::Vector2f m_position;
	
    StateMachine<Boss>* m_pStateMachine;

	std::vector<sf::Vector2f> m_idlePositions = { {95,300 },{ 89, 304 }, { 91,300 }, { 99,294 }, { 108,289 }, { 113,287 }, { 115,287 }, { 113,291 }, { 105,294 }, { 99,300 } };
	std::vector<sf::Vector2f> m_groundSmashPositions = { {169,271}, {168,254}, {170,203}, {172,170}, {173,157}, {174,161}, {174,166}, {172,179}, {181,227}, {175,289} };
	std::vector<sf::Vector2f> m_grabRockPosition = { {159, 142}, {157, 144}, {152, 152}, {147, 162}, {138, 175},{129, 199}, {130, 255}, {180, 347}, {194, 353} };
	std::vector<sf::Vector2f> m_throwPositions = { {160,325}, {174,321}, {182,315}, {184,317}, {184,321}, {182,322}, {182,320}, {182,294}, {186,247}, {187,222} };
	std::vector<sf::Vector2f> m_retreatPositions = { {169,312}, {169,312}, {168,314}, {165,313}, {168,316}, {172,314}, {183,314}, {203,317}, {229,319}, {240,321} };
	std::vector<sf::Vector2f> m_RidlePositions = { {406,298}, { 411,302 }, {407,298}, {401,293}, {394,288}, {386,284}, {386,285}, {389,288}, {393,293}, {402,299} };
	std::vector<sf::Vector2f> m_RgroundSmashPositions = { {327,271}, {328,253}, {326,204}, {326,171}, {325,156}, {324,160}, {323,165}, {321,178}, {321,226}, {322,288} };
	std::vector<sf::Vector2f> m_RgrabRockPosition = { {293, 346}, {296, 343}, {299, 339}, {305, 330}, {318, 313},{334, 295}, {348, 271}, {336, 215}, {331, 206} };
	std::vector<sf::Vector2f> m_RthrowPositions = { {336,299}, {317,314}, {314,318}, {314,321}, {314,322}, {314,324}, {316,321}, {316,296}, {315,246}, {314,221} };
	std::vector<sf::Vector2f> m_RretreatPositions = { {329,312}, {331,312}, {336,312}, {334,311}, {328,310}, {302,305}, {268,307}, {246,312}, {240,317}, {240,321} };
public:
    void OnInitialize() override;
	void SetAnimation(const std::string& _name);
	void OnAnimationEnd(const std::string& _animationIndex) override;
	void OnFrameChange(const std::string& _animationIndex, int _frame) override;
    void OnUpdate() override;
	void TakeDamage(int _damage);
	BossActionType GetCurrentAction();
    void StartAttack(BossActionType action);
	float GetDistanceToPlayer();

	bool CheckState(BossActionType newState);

	bool m_isGroundSmashing = false;
	bool m_isRetreating = false;
	bool m_GrabRock = false;
	bool m_isThrowing = false;
	bool m_isIdle = false;

private:
	friend class BossAction_GrabRock;
	friend class BossAction_GroundSmash;
	friend class BossAction_Throwing;
	friend class BossAction_Retreat;
	friend class BossAction_Idle;
};

