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
	m_Entity = _entity;

	setTexture(*(GET_MANAGER(ResourceManager)->getTexture(_path)));

	deserialize(loadFromFile("../../../res/" + _path + ".json"));
}

void SpriteSheet::addAnimation(Animation* _animation)
{
	m_Animations.push_back(_animation);
}

void SpriteSheet::setAnimation(int _index)
{
	_ASSERT(_index <= m_Animations.size());

	m_AnimationIndex = _index;
	m_AnimationFrame = 0;

	sf::Vector2i pos = sf::Vector2i(m_AnimationFrame * m_Animations[m_AnimationIndex]->m_Size.x, m_AnimationIndex * m_Animations[m_AnimationIndex]->m_Size.y);
	sf::Vector2i size = sf::Vector2i(m_Animations[m_AnimationIndex]->m_Size.x, m_Animations[m_AnimationIndex]->m_Size.y);
	setTextureRect(sf::IntRect(pos, size));
}

std::string SpriteSheet::getCurrentAnimationName()
{
	return m_Animations[m_AnimationIndex]->m_Name;
}

void SpriteSheet::deserialize(const nlohmann::json& _json)
{
	for (auto& animation : _json["animations"].items())
	{
		Animation* anim = new Animation;
		animation.value().at("frames").get_to(anim->m_MaxFrame);
		animation.value().at("loop").get_to(anim->m_Looping);
		anim->m_Name = animation.key();

		anim->m_Size = sf::Vector2i(_json["frame_size"]["width"], _json["frame_size"]["height"]);

		animation.value().at("frame_time").get_to(anim->m_FrameTime);

		addAnimation(anim);
	}
}

void SpriteSheet::update()
{
	float dt = GET_MANAGER(GameManager)->GetDeltaTime();
	m_Timer += dt;
	if (m_Timer >= m_Animations[m_AnimationIndex]->m_FrameTime)
	{
		m_Timer = 0;

		++m_AnimationFrame %= m_Animations[m_AnimationIndex]->m_MaxFrame;

		if (m_AnimationFrame == 0 && !m_Animations[m_AnimationIndex]->m_Looping) // On animation end
		{
			m_Entity->OnAnimationEnd(m_AnimationIndex);
		}
		
		sf::Vector2i pos = sf::Vector2i(m_AnimationFrame * m_Animations[m_AnimationIndex]->m_Size.x, m_AnimationIndex * m_Animations[m_AnimationIndex]->m_Size.y);
		sf::Vector2i size = sf::Vector2i(m_Animations[m_AnimationIndex]->m_Size.x, m_Animations[m_AnimationIndex]->m_Size.y);
		setTextureRect(sf::IntRect(pos, size));
	}
}
