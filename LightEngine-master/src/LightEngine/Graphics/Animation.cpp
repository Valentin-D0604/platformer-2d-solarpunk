#include "Animation.h"

Animation::Animation(std::string _name, sf::Vector2i _size, int _maxFrame, float _frameTime, bool _looping)
{
	m_Name = _name;
	m_Size = _size;
	m_MaxFrame = _maxFrame;
	m_FrameTime = _frameTime;
	m_Looping = _looping;
}
