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
	std::unordered_map<std::string, Animation*> m_animations;
	std::unordered_map<std::string, sf::IntRect> m_sprites;
	std::string m_animationName;
	int m_animationFrame;
	float m_timer;
	bool m_playing;
	
public:
	SpriteSheet(std::string _path);
	SpriteSheet(Entity* _entity, SpriteSheet* _copy);
	void AddAnimation(Animation* _animation);
	void SetAnimation(const std::string& _name);
	void SetSprite(const std::string& _name);
	void SetPlaying(bool _playing);
	std::string GetCurrentAnimationName();
	virtual void Deserialize(const nlohmann::ordered_json& _json);
	virtual void Update() override;

	friend class ResourceManager;
};
