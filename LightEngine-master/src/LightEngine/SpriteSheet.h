#pragma once
#include "Sprite.h"

class Animation;
class Entity;

class SpriteSheet: public Sprite
{
	Entity* m_entity;
	sf::Texture* m_texture;
	std::vector<Animation*> m_animations;
	int m_animationIndex;
	int m_animationFrame;
	float m_timer;
	
public:
	SpriteSheet(Entity* _entity);
	void addAnimation(Animation* _animation);
	void setAnimation(int _index);
	std::string getCurrentAnimationName();
	virtual void update() override;
};