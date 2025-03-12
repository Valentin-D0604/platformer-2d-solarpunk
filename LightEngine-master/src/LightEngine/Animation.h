#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
	sf::Vector2f m_size;
	int m_maxFrame;
	int m_frameTime;
	bool m_looping;

	friend class SpriteSheet;
};

