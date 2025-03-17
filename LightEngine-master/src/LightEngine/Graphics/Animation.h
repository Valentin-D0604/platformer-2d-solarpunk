#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
	std::string m_Name;
	sf::Vector2i m_Size;
	int m_MaxFrame;
	float m_FrameTime;
	bool m_Looping;

	friend class SpriteSheet;
};

