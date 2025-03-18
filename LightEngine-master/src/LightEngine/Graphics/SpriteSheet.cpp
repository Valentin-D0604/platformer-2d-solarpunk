#include "SpriteSheet.h"
#include "../Managers/Managers.h"
#include "Animation.h"
#include "Sprite.h"
#include "../json.hpp"

#include <iostream>

using json = nlohmann::json;

inline json loadFromFile(const std::string& _path) {
	std::ifstream file(_path);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open file " + _path);
	}

	json stream;
	file >> stream;
	return stream;
}


SpriteSheet::SpriteSheet(Entity* _entity, std::string _path)
{
	m_entity = _entity;

	setTexture(*(GET_MANAGER(ResourceManager)->GetTexture(_path)));

	Deserialize(loadFromFile("../../../res/" + _path + ".json"));

	m_playing = true;
}

void SpriteSheet::AddAnimation(Animation* _animation)
{
	m_animations.push_back(_animation);
}

void SpriteSheet::SetAnimation(int _index)
{
	_ASSERT(_index <= m_animations.size());

	m_animationIndex = _index;
	m_animationFrame = 0;

	sf::Vector2i pos = sf::Vector2i(m_animationFrame * m_animations[m_animationIndex]->m_size.x, m_animationIndex * m_animations[m_animationIndex]->m_size.y);
	sf::Vector2i size = sf::Vector2i(m_animations[m_animationIndex]->m_size.x, m_animations[m_animationIndex]->m_size.y);
	setTextureRect(sf::IntRect(pos, size));

	m_playing = true;
}

void SpriteSheet::SetPlaying(bool _playing)
{
	m_playing = _playing;
}

std::string SpriteSheet::GetCurrentAnimationName()
{
	return m_animations[m_animationIndex]->m_name;
}

void SpriteSheet::Deserialize(const nlohmann::json& _json)
{
	for (auto& animation : _json["animations"].items())
	{
		Animation* anim = new Animation;
		animation.value().at("frames").get_to(anim->m_maxFrame);
		animation.value().at("loop").get_to(anim->m_looping);
		anim->m_name = animation.key();

		anim->m_size = sf::Vector2i(_json["frame_size"]["width"], _json["frame_size"]["height"]);

		animation.value().at("frame_time").get_to(anim->m_frameTime);

		AddAnimation(anim);
	}
}

void SpriteSheet::Update()
{
	if (!m_playing)
		return;

	float dt = GET_MANAGER(GameManager)->GetDeltaTime();
	m_timer += dt;
	if (m_timer >= m_animations[m_animationIndex]->m_frameTime)
	{
		m_timer = 0;

		++m_animationFrame %= m_animations[m_animationIndex]->m_maxFrame;

		if (m_animationFrame == 0 && !m_animations[m_animationIndex]->m_looping) // On animation end
		{
			m_playing = false;
			m_entity->OnAnimationEnd(m_animationIndex);
			return;
		}

		m_entity->OnFrameChange(m_animationIndex, m_animationFrame);
		
		sf::Vector2i pos = sf::Vector2i(m_animationFrame * m_animations[m_animationIndex]->m_size.x, m_animationIndex * m_animations[m_animationIndex]->m_size.y);
		sf::Vector2i size = sf::Vector2i(m_animations[m_animationIndex]->m_size.x, m_animations[m_animationIndex]->m_size.y);
		setTextureRect(sf::IntRect(pos, size));
	}
}
