#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
	std::string m_name;
	sf::Vector2i m_size;
	int m_maxFrame;
	float m_frameTime;
	bool m_looping;

	friend class SpriteSheet;
};

