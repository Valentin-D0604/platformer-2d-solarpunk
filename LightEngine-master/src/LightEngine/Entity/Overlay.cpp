#include "Overlay.h"
#include "../Graphics/Sprite.h"
#include "../Utils/Utils.h"
#include "../Managers/Managers.h"
#include <iostream>


void Overlay::OnInitialize()
{
	m_sprite = new Sprite;
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));
	m_sprite->setScale(50, 50);
}

void Overlay::OnUpdate()
{
	if (m_targetAlpha == 0)
	{
		m_currentAlpha -= (GET_MANAGER(GameManager)->GetDeltaTime() / m_outDuration);
	}

	else if (m_targetAlpha == 1)
	{
		m_currentAlpha += (GET_MANAGER(GameManager)->GetDeltaTime() / m_inDuration);
	}
	
	sf::Color color = sf::Color(100, 0, 0, m_currentAlpha);
	color.a = m_currentAlpha;
	m_sprite->setColor(color);

	if (m_nextOut && m_currentAlpha >= 1)
	{
		m_targetAlpha = 0;
	}

	else if (m_currentAlpha <= 0)
	{
		m_targetAlpha = -1;
	}

	if (m_player->ToDestroy() || m_player == nullptr)
		return;

	SetPosition(m_player->GetPosition() + sf::Vector2f(-1000, -500));

	//std::cout << "Position: " << GetPosition().x << ", " << GetPosition().y << " // Opacity" << m_currentAlpha << "//" << color.a << std::endl;
}

void Overlay::SetPlayer(Entity* _player)
{
	m_player = _player;
}

void Overlay::FadeIn(float _duration)
{
	m_targetAlpha = 1;
	m_inDuration = _duration;
}

void Overlay::FadeOut(float _duration)
{
	m_targetAlpha = 0;
	m_outDuration = _duration;
}

void Overlay::FadeInOut(float _inDuration, float _outDuration)
{
	m_nextOut = true;
	m_inDuration = _inDuration;
	m_outDuration = _outDuration;

	m_targetAlpha = 1;
}
