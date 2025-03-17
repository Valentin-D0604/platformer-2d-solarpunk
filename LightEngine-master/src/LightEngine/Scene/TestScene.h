#pragma once
#include "Scene.h"

class PhysicsEntity;
class DummyEntity;
class Player;
class Mob1;
class Mob2;
class Mob3;

class Platform;

class TestScene : public Scene
{
public:

	Player* pEntity1;
	DummyEntity* pEntity2;
	Mob1* monster;
	Mob2* range;
	Mob3* Explode;
	DummyEntity* pEntitySelected;

	Platform* pPlatform;

	Entity* pEntitySelected;

	enum Tag
	{
		player,
		mob1,
		mob2,
		mob3,
		bullet,
		platform

	};

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	
	Player* GetPlayer();

	void GetTag() { return; }
};


