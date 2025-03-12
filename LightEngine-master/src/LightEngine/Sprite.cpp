#include "Sprite.h"

void SpriteSheet::setAnimation(int _index)
{
	_ASSERT(_index > m_animations.size());

	m_animationIndex = _index;
	m_animationFrame = 0;
}
