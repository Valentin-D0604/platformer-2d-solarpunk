#include "SpriteSheet.h"
#include "../Managers/Managers.h"
#include "Animation.h"
#include "Sprite.h"

SpriteSheet::SpriteSheet(Entity* _entity)
{
	m_Entity = _entity;
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

