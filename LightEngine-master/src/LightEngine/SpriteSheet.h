#pragma once
#include "Sprite.h"

class Animation;

class SpriteSheet: Sprite
{
	std::vector<Animation*> m_animations;
	int m_animationIndex;
	int m_animationFrame;
	float m_timer;
	
public:
	void setAnimation(int _index);
	virtual void update() override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};