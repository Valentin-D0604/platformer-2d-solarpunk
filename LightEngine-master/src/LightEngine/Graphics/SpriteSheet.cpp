#include "SpriteSheet.h"
#include "../Managers/Managers.h"
#include "../Entity/Entity.h"
#include "Animation.h"
#include "Sprite.h"
#include "../json.hpp"

#include <iostream>

using json = nlohmann::ordered_json;

inline json loadFromFile(const std::string& _path) {
	std::ifstream file(_path);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open file " + _path);
	}

	json stream;
	file >> stream;
	return stream;
}


SpriteSheet::SpriteSheet(std::string _path)
{
	setTexture(*(GET_MANAGER(ResourceManager)->GetTexture(_path)));

	Deserialize(loadFromFile("../../../res/" + _path + ".json"));
}

SpriteSheet::SpriteSheet(Entity* _entity, SpriteSheet* _copy)
{
	setTexture(*(_copy->getTexture()));
	m_entity = _entity;

	m_playing = _copy->m_playing;
	m_animations = _copy->m_animations;
	m_sprites = _copy->m_sprites;
	m_animationName = _copy->m_animationName;
}

void SpriteSheet::AddAnimation(Animation* _animation)
{
	m_animations[_animation->m_name] = _animation;
}

void SpriteSheet::SetAnimation(const std::string& _name)
{
	m_animationFrame = 0;
	m_animationName = _name;

 	sf::Vector2i pos = sf::Vector2i(m_animationFrame * m_animations[_name]->m_size.x, m_animations[m_animationName]->m_line * m_animations[_name]->m_size.y);
	sf::Vector2i size = sf::Vector2i(m_animations[_name]->m_size.x, m_animations[_name]->m_size.y);
	setTextureRect(sf::IntRect(pos, size));

	m_playing = true;
}

void SpriteSheet::SetSprite(const std::string& _name)
{
	setTextureRect(m_sprites[_name]);
}

void SpriteSheet::SetPlaying(bool _playing)
{
	m_playing = _playing;
}

std::string SpriteSheet::GetCurrentAnimationName()
{
	return m_animationName;
}

void SpriteSheet::Deserialize(const nlohmann::ordered_json& _json)
{
	if (_json["structure"] == "grid")
	{
		m_playing = false;
		sf::Vector2i size = sf::Vector2i(_json["frame_size"]["width"], _json["frame_size"]["height"]);

		for (auto& element : _json["elements"].items())
		{
			sf::Vector2i pos = sf::Vector2i(element.value().at("x"), element.value().at("y"));
			m_sprites[element.key()] = sf::IntRect(pos, size);
		}
	}

	else if (_json["structure"] == "single" || _json["structure"] == "byRow")
	{
		int i = 0;
		m_playing = true;
		for (auto& animation : _json["animations"].items())
		{
			Animation* anim = new Animation;
			animation.value().at("frames").get_to(anim->m_maxFrame);
			animation.value().at("loop").get_to(anim->m_looping);
			anim->m_name = animation.key();

			anim->m_size = sf::Vector2i(_json["frame_size"]["width"], _json["frame_size"]["height"]);

			animation.value().at("frame_time").get_to(anim->m_frameTime);

			anim->m_line = i++;

			AddAnimation(anim);
		}
	}
}

void SpriteSheet::Update()
{
	if (!m_playing)
		return;

	float dt = GET_MANAGER(GameManager)->GetDeltaTime();
	m_timer += dt;
	if (m_timer >= m_animations[m_animationName]->m_frameTime)
	{
		m_timer = 0;

		++m_animationFrame %= m_animations[m_animationName]->m_maxFrame;

		if (m_animationFrame == 0 && !m_animations[m_animationName]->m_looping) // On animation end
		{
			m_playing = false;
			m_entity->OnAnimationEnd(m_animationName);
			return;
		}

		m_entity->OnFrameChange(m_animationName, m_animationFrame);

		sf::Vector2i pos = sf::Vector2i(m_animationFrame * m_animations[m_animationName]->m_size.x, m_animations[m_animationName]->m_line * m_animations[m_animationName]->m_size.y);
		sf::Vector2i size = sf::Vector2i(m_animations[m_animationName]->m_size.x, m_animations[m_animationName]->m_size.y);
		setTextureRect(sf::IntRect(pos, size));
	}
}
