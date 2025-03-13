#pragma once
#include "Action.h"
#include "Mob2.h"

class Mob2Action_Walking : public Action<Mob2>
{
	sf::Vector2f dir = { 1,0 };
public:
	void OnStart(Mob2* player) override;
	void OnUpdate(Mob2* player) override;
	void OnEnd(Mob2* player) override;
};

class Mob2Action_Chasing : public Action<Mob2>
{
public:
	void OnStart(Mob2* player) override;
	void OnUpdate(Mob2* player) override;
	void OnEnd(Mob2* player) override;
};

class Mob2Action_Attacking : public Action<Mob2>
{
public:
	void OnStart(Mob2* player) override;
	void OnUpdate(Mob2* player) override;
	void OnEnd(Mob2* player) override;
};

class Mob2Action_Idle : public Action<Mob2>
{
public:
	void OnStart(Mob2* player) override;
	void OnUpdate(Mob2* player) override;
	void OnEnd(Mob2* player) override;
};

