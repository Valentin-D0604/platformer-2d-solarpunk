#include "Hands.h"

#include "../Actions/BossAction.h"
#include "../Conditions/BossCondition.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/Sprite.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"

#include "../Utils/Utils.h"

#include <iostream>
#include <cmath>

void Hand::OnInitialize()
{

    m_animationIndex = 0;
    m_frameTimer = 0.0f;
}

void Hand::PositionSettings(std::vector<sf::Vector2f> _idlePositions, std::vector<sf::Vector2f> _groundSmashPositions, std::vector<sf::Vector2f> _grabRockPosition, std::vector<sf::Vector2f> _throwPositions, std::vector<sf::Vector2f> _retreatPositions)
{
	idlePositions = _idlePositions;
	groundSmashPositions = _groundSmashPositions;
    grabRockPosition = _grabRockPosition;
	throwPositions = _throwPositions;
	retreatPositions = _retreatPositions;
}


void Hand::OnUpdate() {
	BossActionType Type = GetOwner()->GetCurrentAction();
	SpriteSheet* spriteSheet = dynamic_cast<SpriteSheet*>(m_sprite);
    if (timerisOn)
    {
        m_timer -= GetDeltaTime();
		if (m_timer <= 0.0f)
		{
			timerisOn = false;
			m_timer = 4.0f;
		}
    }
}

void Hand::OnCollision(Entity* _collidedWith) 
{
    if (_collidedWith->IsTag(TestScene::Tag::bullet))
    {
		_collidedWith->Destroy();
        GetOwner()->TakeDamage(1);
	}
    if (_collidedWith->IsTag(TestScene::Tag::player))
    {
		Player* player = dynamic_cast<Player*>(_collidedWith);
        if (timerisOn == false)
        {
			timerisOn = true;
            player->TakeDamage(1);
        }
    }
}

// ----------------------  FONCTIONS MOUVEMENT ----------------------
// 
// Fonction pour jouer une animation en lisant les positions
void Hand::PlayAnimation(const std::vector<sf::Vector2f> positions) {
    m_frameTimer += GetDeltaTime();

    if (m_frameTimer >= FRAME_DURATION) {
        m_frameTimer = 0.0f;
        m_animationIndex++;

        if (m_animationIndex >= positions.size()) {
            m_animationIndex = 0; // Boucle sur l'animation
        }
    }
	sf::Vector2f position = GetOwner()->GetPosition(0,0);
    SetPosition(positions[m_animationIndex].x + position.x, positions[m_animationIndex].y + position.y);
}

void Hand::SetOwner(Boss* _owner)
{
    m_owner = _owner;

    if (m_isLeft)
    {
        m_sprite = new SpriteSheet(this,(GET_MANAGER(ResourceManager)->GetSpriteSheet("left_hand")));
        dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("idle");
        SetPosition(GetPosition().x + 89, GetPosition().y + 304);

    }
    else
    {
        m_sprite = new SpriteSheet(this,(GET_MANAGER(ResourceManager)->GetSpriteSheet("right_hand")));
        dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("idle");
        SetPosition(GetPosition().x + 411, GetPosition().y + 302);
    }
    m_collider = new RectangleCollider(GetPosition(), { 100, 100 });
    m_collider->SetGizmo(true);
}