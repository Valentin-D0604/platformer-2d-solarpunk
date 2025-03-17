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
	Entity* m_entity;
	sf::Texture* m_texture;
	std::vector<Animation*> m_animations;
	int m_animationIndex;
	int m_animationFrame;
	float m_timer;
	
public:
	SpriteSheet(Entity* _entity, std::string _path);
	void AddAnimation(Animation* _animation);
	void SetAnimation(int _index);
	std::string GetCurrentAnimationName();
	virtual void Deserialize(const nlohmann::json& _json);
	virtual void Update() override;
};
