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
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));
	sf::Vector2f pos(0, 0);
	sf::Vector2f size = sf::Vector2f(m_sprite->getTexture()->getSize());
    m_collider = new RectangleCollider(pos, size);
    m_collider->SetGizmo(true);
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

// Mise à jour des actions de la main
void Hand::OnUpdate() {
	BossActionType Type = GetOwner()->GetCurrentAction();

    if (Type == BossActionType::groundSmash) {
        PlayAnimation(groundSmashPositions);
    }
    else if (Type == BossActionType::grabRock) {
        PlayAnimation(grabRockPosition);
    }
    else 
    {
		std::cout << GetPosition().x << " " << GetPosition().y << std::endl;
		std::cout << "hand side :" << m_isLeft << std::endl;
		PlayAnimation(idlePositions);
    }
}

// Détection de collision (ex: le projectile spécial qui stun la main)
void Hand::OnCollision(Entity* _collidedWith) {
    if (_collidedWith->IsTag(TestScene::Tag::bullet)) {
    }
}

// ----------------------  LOGIQUE ACTIONS ----------------------


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
	this->SetPosition(_owner->GetPosition().x,_owner->GetPosition().y);
    if (m_isLeft)
    {
        SetPosition(GetPosition().x + 89, GetPosition().y + 304);
    }
    else
    {
        SetPosition(GetPosition().x + 411, GetPosition().y + 302);
    }
}