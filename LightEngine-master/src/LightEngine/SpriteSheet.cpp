#include "SpriteSheet.h"
#include "Managers.h"
#include "Animation.h"
#include "Sprite.h"

SpriteSheet::SpriteSheet(Entity* _entity)
{
	m_entity = _entity;
}

void SpriteSheet::addAnimation(Animation* _animation)
{
	m_animations.push_back(_animation);
}

void SpriteSheet::setAnimation(int _index)
{
	_ASSERT(_index <= m_animations.size());

	m_animationIndex = _index;
	m_animationFrame = 0;

	sf::Vector2i pos = sf::Vector2i(m_animationFrame * m_animations[m_animationIndex]->m_size.x, m_animationIndex * m_animations[m_animationIndex]->m_size.y);
	sf::Vector2i size = sf::Vector2i(m_animations[m_animationIndex]->m_size.x, m_animations[m_animationIndex]->m_size.y);
	setTextureRect(sf::IntRect(pos, size));
}

std::string SpriteSheet::getCurrentAnimationName()
{
	return m_animations[m_animationIndex]->m_name;
}

void SpriteSheet::update()
{
	float dt = GET_MANAGER(GameManager)->GetDeltaTime();
	m_timer += dt;

	if (m_timer >= m_animations[m_animationIndex]->m_frameTime)
	{
		m_timer = 0;

		++m_animationFrame %= m_animations[m_animationIndex]->m_maxFrame;

		if (m_animationFrame == 0 && !m_animations[m_animationIndex]->m_looping) // On animation end
		{
			m_entity->OnAnimationEnd(m_animationIndex);
		}
		
		sf::Vector2i pos = sf::Vector2i(m_animationFrame * m_animations[m_animationIndex]->m_size.x, m_animationIndex * m_animations[m_animationIndex]->m_size.y);
		sf::Vector2i size = sf::Vector2i(m_animations[m_animationIndex]->m_size.x, m_animations[m_animationIndex]->m_size.y);
		setTextureRect(sf::IntRect(pos, size));
	}
}

