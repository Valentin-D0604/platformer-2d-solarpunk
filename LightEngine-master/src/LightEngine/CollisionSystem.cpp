#include "CollisionSystem.h"

void CollisionSystem::resolveCollision(sf::RectangleShape& moving, const sf::RectangleShape& staticRect)
{
	sf::FloatRect movingBounds = moving.getGlobalBounds();
	sf::FloatRect staticBounds = staticRect.getGlobalBounds();

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
			moving.move(fromLeft ? -minOverlapX : minOverlapX, 0);
		}
		else
		{
			moving.move(0, fromTop ? -minOverlapY : minOverlapY);
		}
	}
}

void CollisionSystem::test()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Resolution");

    // Création des rectangles
    sf::RectangleShape player(sf::Vector2f(100, 100));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(300, 250);

    sf::RectangleShape obstacle(sf::Vector2f(100, 100));
    obstacle.setFillColor(sf::Color::Red);
    obstacle.setPosition(500, 250); // Position fixe

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Déplacement du joueur avec correction de collision
        sf::Vector2f oldPos = player.getPosition(); // Sauvegarde l'ancienne position

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-2, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(2, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, 2);

        // Corriger la collision après le déplacement
        resolveCollision(player, obstacle);

        window.clear();
        window.draw(player);
        window.draw(obstacle);
        window.display();
    }
}