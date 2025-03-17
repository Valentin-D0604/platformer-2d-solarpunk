#pragma once
#include "Condition.h"
#include "../Entity/Mob3.h"

class Mob3Condition_IsWalking : public Condition <Mob3>
{
public:
	bool OnTest(Mob3* owner) override;
};

class Mob3Condition_IsChasing : public Condition<Mob3>
{
public:
	bool OnTest(Mob3* owner) override;
};

class Mob3Condition_IsAttacking : public Condition<Mob3>
{
public:
	bool OnTest(Mob3* owner) override;
};

class Mob3Condition_IsIdle : public Condition<Mob3>
{
public:
	bool OnTest(Mob3* owner) override;
};
