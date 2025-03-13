#pragma once
#include "Sprite.h"

class Animation;
class Entity;

class SpriteSheet: public Sprite
{
	Entity* m_Entity;
	sf::Texture* m_Texture;
	std::vector<Animation*> m_Animations;
	int m_AnimationIndex;
	int m_AnimationFrame;
	float m_Timer;
	
public:
	SpriteSheet(Entity* _entity);
	void addAnimation(Animation* _animation);
	void setAnimation(int _index);
	std::string getCurrentAnimationName();
	virtual void update() override;
};