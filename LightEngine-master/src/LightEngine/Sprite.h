#pragma once
#include "SFML/Graphics.hpp"

class Animation;

class SpriteSheet: sf::Sprite
{
	sf::Sprite* m_spriteSheet;
	std::vector<Animation*> m_animations;
	int m_animationIndex;
	int m_animationFrame;
	
public:

	void setAnimation(int _index);
};