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

    if (timerisOn)
    {
        m_timer -= GetDeltaTime();
		if (m_timer <= 0.0f)
		{
			timerisOn = false;
			m_timer = 4.0f;
		}
    }

    if (Type == BossActionType::groundSmash) {
        dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("slam");
        PlayAnimation(groundSmashPositions);
    }
    else if (Type == BossActionType::grabRock) {
        dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("grab");
        PlayAnimation(grabRockPosition);
	}
	else if (Type == BossActionType::throwRock) {
		dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("throw");
		PlayAnimation(throwPositions);
	}
	else if (Type == BossActionType::retreat) {
		dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("retreat");
		PlayAnimation(retreatPositions);
	}
    else 
    {
		std::cout << GetPosition().x << " " << GetPosition().y << std::endl;
		std::cout << "hand side :" << m_isLeft << std::endl;
		dynamic_cast<SpriteSheet*>(m_sprite)->SetAnimation("idle");
		PlayAnimation(idlePositions);
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

    SetPosition(positions[m_animationIndex].x + GetOwner()->GetPosition().x, positions[m_animationIndex].y + GetOwner()->GetPosition().y);
	std::cout << positions[m_animationIndex].x + GetOwner()->GetPosition().x << std::endl;
}

void Hand::SetOwner(Boss* _owner)
{
    m_owner = _owner;

    if (m_isLeft)
    {
        m_sprite = ((GET_MANAGER(ResourceManager)->GetSpriteSheet("left_hand")));
        SetPosition(GetPosition().x + 89, GetPosition().y + 304);

    }
    else
    {
        m_sprite = ((GET_MANAGER(ResourceManager)->GetSpriteSheet("right_hand")));
        SetPosition(GetPosition().x + 411, GetPosition().y + 302);
    }
    sf::Vector2f size = sf::Vector2f(m_sprite->getTexture()->getSize());
    m_collider = new RectangleCollider(GetPosition(), size);
    m_collider->SetGizmo(true);
}