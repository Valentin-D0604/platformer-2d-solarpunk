#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
	std::string m_Name;
	sf::Vector2i m_Size;
	int m_MaxFrame;
	float m_FrameTime;
	bool m_Looping;

public:
	Animation(std::string _name, sf::Vector2i _size, int _maxFrame, float _frameTime, bool _looping);

	friend class SpriteSheet;
};

