#pragma once
#include "Action.h"
#include "Mob1.h"

class Mob1Action_Walking : public Action<Mob1>
{
	sf::Vector2f dir = {1,0 };
public:
	void OnStart(Mob1* player) override;
	void OnUpdate(Mob1* player) override;
	void OnEnd(Mob1* player) override;
};

class Mob1Action_Chasing : public Action<Mob1>
{
public:
	void OnStart(Mob1* player) override;
	void OnUpdate(Mob1* player) override;
	void OnEnd(Mob1* player) override;
};

class Mob1Action_Attacking : public Action<Mob1>
{
public:
	void OnStart(Mob1* player) override;
	void OnUpdate(Mob1* player) override;
	void OnEnd(Mob1* player) override;
};

class Mob1Action_Idle : public Action<Mob1>
{
public:
	void OnStart(Mob1* player) override;
	void OnUpdate(Mob1* player) override;
	void OnEnd(Mob1* player) override;
};

