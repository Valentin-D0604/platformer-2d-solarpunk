#pragma once
#include "../Scene/Scene.h"

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
	Mob3* explode;

	Platform* pPlatform;

	Entity* pEntitySelected;

	bool m_firstCreation = true;
	enum Tag
	{
		player,
		mob1,
		mob2,
		mob3,
		PowerUp,
		bullet,
		platform

	};

	void OnInitialize() override;
	void OnEvent(const sf::Event& _event) override;
	void OnUpdate() override;
	void Destroy();
	void LoadFromText();
	Player* GetPlayer();

	void GetTag() { return; }
};


