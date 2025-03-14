#pragma once
#include "Action.h"
#include "Mob3.h"

class Mob3Action_Walking : public Action<Mob3>
{
	sf::Vector2f dir = { 1,0 };
public:
	void OnStart(Mob3* player) override;
	void OnUpdate(Mob3* player) override;
	void OnEnd(Mob3* player) override;
};

class Mob3Action_Chasing : public Action<Mob3>
{
public:
	void OnStart(Mob3* player) override;
	void OnUpdate(Mob3* player) override;
	void OnEnd(Mob3* player) override;
};

class Mob3Action_Attacking : public Action<Mob3>
{
public:
	void OnStart(Mob3* player) override;
	void OnUpdate(Mob3* player) override;
	void OnEnd(Mob3* player) override;
};

class Mob3Action_Idle : public Action<Mob3>
{
public:
	void OnStart(Mob3* player) override;
	void OnUpdate(Mob3* player) override;
	void OnEnd(Mob3* player) override;
};

