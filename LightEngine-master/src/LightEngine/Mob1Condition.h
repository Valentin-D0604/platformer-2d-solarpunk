#pragma once
#include "Condition.h"
#include "Mob1.h"

class Mob1Condition_IsWalking : public Condition <Mob1>
{
public:
	bool OnTest(Mob1* owner) override;
};

class Mob1Condition_IsChasing : public Condition<Mob1>
{
public:
	bool OnTest(Mob1* owner) override;
};

class Mob1Condition_IsAttacking : public Condition<Mob1>
{
public:
	bool OnTest(Mob1* owner) override;
};

class Mob1Condition_IsIdle : public Condition<Mob1>
{
public:
	bool OnTest(Mob1* owner) override;
};
