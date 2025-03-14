#pragma once
#include "Condition.h"
#include "Mob2.h"

class Mob2Condition_IsWalking : public Condition <Mob2>
{
public:
	bool OnTest(Mob2* owner) override;
};

class Mob2Condition_IsChasing : public Condition<Mob2>
{
public:
	bool OnTest(Mob2* owner) override;
};

class Mob2Condition_IsAttacking : public Condition<Mob2>
{
public:
	bool OnTest(Mob2* owner) override;
};

class Mob2Condition_IsIdle : public Condition<Mob2>
{
public:
	bool OnTest(Mob2* owner) override;
};
