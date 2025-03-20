#pragma once
#include "../Scene/Scene.h"

class PhysicsEntity;
class DummyEntity;
class Player;
class Mob1;
class Mob2;
class Mob3;

class Platform;
class Overlay;

class TestScene : public Scene
{
public:

	DummyEntity* pEntity2;
	Player* m_player;

	Overlay* m_overlay;

	bool m_firstCreation = true;
	enum Tag
	{
		player,
		mob1,
		mob2,
		mob3,
		boss,
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


