#include "Platform.h"
#include "TestScene.h"
#include "RectangleCollider.h"
#include <iostream>

void Platform::OnInitialize() {
	m_collider = new RectangleCollider(GetPosition(), sf::Vector2f(100, 10));
	m_collider->setGizmo(true);
	SetTag(TestScene::OBJECT);
}

void Platform::onCollision(sf::CircleShape& player, const sf::RectangleShape& plat) {
	
	sf::FloatRect movingBounds = player.getGlobalBounds();
	sf::FloatRect staticBounds = plat.getGlobalBounds();

	if (movingBounds.intersects(staticBounds))
	{
		float overlapLeft = movingBounds.left + movingBounds.width - staticBounds.left;
		float overlapRight = staticBounds.left + staticBounds.width - movingBounds.left;
		float overlapTop = movingBounds.top + movingBounds.height - staticBounds.top;
		float overlapBottom = staticBounds.top + staticBounds.height - movingBounds.top;

		bool fromLeft = overlapLeft < overlapRight;
		bool fromTop = overlapTop < overlapBottom;

		float minOverlapX = fromLeft ? overlapLeft : overlapRight;
		float minOverlapY = fromTop ? overlapTop : overlapBottom;

		// Repousser dans la direction la plus courte (horizontale ou verticale)
		if (minOverlapX < minOverlapY)
		{
			player.move(fromLeft ? -minOverlapX : minOverlapX, 0);
		}
		else
		{
			player.move(0, fromTop ? -minOverlapY : minOverlapY);
		}
	}
}

void Platform::OnUpdate() {

}