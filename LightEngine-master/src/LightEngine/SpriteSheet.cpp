#include "SpriteSheet.h"
#include "Managers.h"
#include "Animation.h"

void SpriteSheet::setAnimation(int _index)
{
	_ASSERT(_index > m_animations.size());

	m_animationIndex = _index;
	m_animationFrame = 0;
}

void SpriteSheet::update()
{
	float dt = GET_MANAGER(GameManager)->GetDeltaTime();
	m_timer += dt;

	if (m_timer >= m_animations[m_animationIndex]->m_frameTime)
	{
		++m_animationFrame %= m_animations[m_animationIndex]->m_maxFrame;
	}
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}
