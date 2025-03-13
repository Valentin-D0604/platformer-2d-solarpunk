#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
	std::string m_name;
	sf::Vector2i m_size;
	int m_maxFrame;
	float m_frameTime;
	bool m_looping;

public:
	Animation(std::string _name, sf::Vector2i _size, int _maxFrame, float _frameTime, bool _looping);

	friend class SpriteSheet;
};

