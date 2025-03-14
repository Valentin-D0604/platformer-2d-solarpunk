#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class CollisionSystem
{
public:
    void resolveCollision(sf::RectangleShape& moving, const sf::RectangleShape& staticRect);
	void test();
};