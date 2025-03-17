#pragma once
#include "Sprite.h"

#pragma region Extneral Dependencies

#include "../json.hpp"
#include <fstream>
#include <string>

#pragma endregion

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
	SpriteSheet(Entity* _entity, std::string _path);
	void addAnimation(Animation* _animation);
	void setAnimation(int _index);
	std::string getCurrentAnimationName();
	virtual void deserialize(const nlohmann::json& _json);
	virtual void update() override;
};
