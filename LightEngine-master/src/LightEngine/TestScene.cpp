#include "TestScene.h"

#include "DummyEntity.h"

#include "Debug.h"

#include "Player.h"

#include "Platform.h"

#include "Mob1.h"
#include "Mob2.h"

#include "Boss.h"

void TestScene::OnInitialize()
{
	pEntity1 = CreateEntity<Player>();
	//pEntity1->SetPosition(300, 300);
	//pEntity1->setMass(20);
	//pEntity1->setGravityDirection(sf::Vector2f(0, 1));
	
	pEntity2 = CreateEntity<DummyEntity>();
	pEntity2->SetPosition(500, 500);
	pEntity2->setMass(0);
	pEntity2->setGravityDirection(sf::Vector2f(0, -1));

	//monster = CreateEntity<Mob1>();
	//monster->SetPosition(700, 300);

	range = CreateEntity<Mob2>();
	range->SetPosition(700, 300);

	pEntitySelected = nullptr;

	/*pPlatform = CreateEntity<Platform>();
	pPlatform->SetPosition(400, 400);
	pPlatform->setMass(0);
	pPlatform->setGravityDirection(sf::Vector2f(0, 0));
	pPlatform->onCollision(pEntity1->GetShape(), pPlatform->GetShape());*/

	pBoss = CreateEntity<Boss>();
	pBoss->SetPosition(700, 300);
	pBoss->setMass(10);
	pBoss->setGravityDirection(sf::Vector2f(0, 1));

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
}

Player* TestScene::GetPlayer()
{
	return pEntity1 && pEntity1->IsAlive() ? pEntity1 : nullptr;
}
