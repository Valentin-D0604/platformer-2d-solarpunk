#include "Animation.h"

Animation::Animation(std::string _name, sf::Vector2i _size, int _maxFrame, float _frameTime, bool _looping)
{
	m_name = _name;
	m_size = _size;
	m_maxFrame = _maxFrame;
	m_frameTime = _frameTime;
	m_looping = _looping;
}
