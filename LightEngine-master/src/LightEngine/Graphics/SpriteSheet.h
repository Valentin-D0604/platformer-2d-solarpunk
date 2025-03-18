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
	std::unordered_map<std::string, Animation*> m_animations;
	std::string m_animationName;
	int m_animationFrame;
	float m_timer;
	bool m_playing;
	
public:
	SpriteSheet(Entity* _entity, std::string _path);
	void AddAnimation(Animation* _animation);
	void SetAnimation(const std::string& _name);
	void SetPlaying(bool _playing);
	std::string GetCurrentAnimationName();
	virtual void Deserialize(const nlohmann::ordered_json& _json);
	virtual void Update() override;
};
