#pragma once
#include "Condition.h"
#include "../Entity/Player.h"

class PlayerCondition_IsWalking : public Condition <Player>
{
public:
	bool OnTest(Player* _owner) override;
};

class PlayerCondition_IsJumping : public Condition<Player>
{
public:
	bool OnTest(Player* _owner) override;
};

class PlayerCondition_IsShooting : public Condition<Player>
{
public:
	bool OnTest(Player* _owner) override;
};

class PlayerCondition_IsParrying : public Condition<Player>
{
public:
	bool OnTest(Player* _owner) override;
};

class PlayerCondition_IsIdle : public Condition<Player>
{
public:
	bool OnTest(Player* _owner) override;
};
