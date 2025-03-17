#include "TestScene.h"

#include "../Entity/DummyEntity.h"

#include "../Graphics/Debug.h"

#include "../Entity/Player.h"

#include "Mob1.h"
#include "Mob2.h"
#include "Mob3.h"
#include "Sprite.h"
#include "Managers.h"
#include "../Entity/Mob1.h"

#include "../Platform.h"

void TestScene::OnInitialize()
{
	pEntity1 = CreateEntity<Player>();
	pEntity1->SetPosition(300, 300);
	pEntity1->SetMass(20);
	pEntity1->SetGravityDirection(sf::Vector2f(0, 1));
	
	pEntity2 = CreateEntity<DummyEntity>();
	pEntity2->SetPosition(500, 500);
	pEntity2->setMass(0);
	pEntity2->setGravityDirection(sf::Vector2f(0, -1));
	
	/*monster = CreateEntity<Mob1>();
	monster->SetPosition(100, 300);*/

	range = CreateEntity<Mob2>();
	range->SetPosition(700, 300);
	
	//Explode = CreateEntity<Mob3>();
	//Explode->SetPosition(500, 100);

	pEntitySelected = nullptr;
	createView();
	setCameraZoom(1);


	pPlatform = CreateEntity<Platform>();
	pPlatform->SetPosition(100, 500);
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
	//	TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void TestScene::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	if (pEntity1->IsAlive()) setCameraCenter(pEntity1->GetPosition());
	else {
		setCameraCenter({ 0,0 });
		setCameraZoom(5);
	}
}

Player* TestScene::GetPlayer()
{
	return pEntity1 && pEntity1->IsAlive() ? pEntity1 : nullptr;
}
