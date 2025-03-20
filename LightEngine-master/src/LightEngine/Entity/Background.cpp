#include "Background.h"
#include "../Managers/Managers.h"

void Background::OnInitialize()
{
	m_basePos = sf::Vector2f(800, 100);
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Background1")));
}

void Background::OnUpdate()
{
	if (m_player->ToDestroy() || m_player == nullptr)
		return;
	sf::Vector2f pos = sf::Vector2f(0.8f * m_player->GetPosition().x, 0.95f * m_player->GetPosition().y) + m_basePos;
	//sf::Vector2f pos = m_player->GetPosition();
	SetPosition(pos.x, pos.y);
}

void Background::SetPlayer(Entity* _player)
{
	m_player = _player;
}
