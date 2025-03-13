#pragma once
#include "Action.h"
#include "../Entity/Mob1.h"

class Mob1Action_Walking : public Action<Mob1>
{
	sf::Vector2f m_Dir = {1,0 };
public:
	void OnStart(Mob1* _player) override;
	void OnUpdate(Mob1* _player) override;
	void OnEnd(Mob1* _player) override;
};

class Mob1Action_Chasing : public Action<Mob1>
{
public:
	void OnStart(Mob1* _player) override;
	void OnUpdate(Mob1* _player) override;
	void OnEnd(Mob1* _player) override;
};

class Mob1Action_Attacking : public Action<Mob1>
{
public:
	void OnStart(Mob1* _player) override;
	void OnUpdate(Mob1* _player) override;
	void OnEnd(Mob1* _player) override;
};

class Mob1Action_Idle : public Action<Mob1>
{
public:
	void OnStart(Mob1* _player) override;
	void OnUpdate(Mob1* _player) override;
	void OnEnd(Mob1* _player) override;
};

