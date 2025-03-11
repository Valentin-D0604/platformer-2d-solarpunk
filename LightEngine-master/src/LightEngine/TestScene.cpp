#include "TestScene.h"

#include "DummyEntity.h"

#include "Debug.h"

#include "player.h"

void TestScene::OnInitialize()
{
	pEntity1 = CreateEntity<Player>(100, sf::Color::Red);
	pEntity1->SetPosition(300, 300);
	pEntity1->SetRigidBody(true);
	pEntity1->setMass(20);
	pEntity1->setGravityDirection(sf::Vector2f(0, 1));

	pEntity2 = CreateEntity<PhysicsEntity>(50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);
	pEntity2->setMass(20);
	pEntity2->setGravityDirection(sf::Vector2f(0, -1));

	pEntitySelected = nullptr;
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

void TestScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void TestScene::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}