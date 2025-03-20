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

	m_isVulnerable = false;
	m_isSweeping = false;
	m_isGroundSmashing = false;
	m_isThrowing = false;


}

void Hand::PositionSettings(std::vector<sf::Vector2f> _idlePositions, std::vector<sf::Vector2f> _groundSmashPositions, std::vector<sf::Vector2f> _throwPositions, std::vector<sf::Vector2f> _retreatPositions)
{
	idlePositions = _idlePositions;
	groundSmashPositions = _groundSmashPositions;
	throwPositions = _throwPositions;
	retreatPositions = _retreatPositions;
}

// Mise à jour des actions de la main
void Hand::OnUpdate() {

    if (m_isGroundSmashing) {
        GroundSmash();
        PlayAnimation(groundSmashPositions);
    }
    else if (m_isThrowing) {
        ThrowRock();
        PlayAnimation(throwPositions);
    }
    else 
    {
        Idle();
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

void Hand::GroundSmash() {
    // Descente rapide vers le sol
    float smashSpeed = 500.0f;
    m_velocity = sf::Vector2f(0, smashSpeed); // Descente

}

void Hand::GrabRock() {
    // Créer un gros projectile (rocher)
    TestScene* scene = dynamic_cast<TestScene*>(GetScene());
    if (scene) {
        Bullet* rock = CreateEntity<Bullet>();
        rock->InitBullet(GetPosition(), sf::Vector2f(0, -1), this); // Lancer vers le haut
        rock->SetMass(5); // Plus lourd qu'un projectile normal
        rock->SetGravityDirection(sf::Vector2f(0, 1)); // Tombe vers le bas

        // Ajouter une force pour lancer le rocher vers le haut
		rock->SetSpeed(1000.0f);
    }
}

void Hand::HandleStun() {
    Stop(); // Arrêter tout mouvement
    m_timer -= GetDeltaTime();
    if (m_timer <= 0) {
        m_isVulnerable = false;
    }
}

// ----------------------  FONCTIONS MOUVEMENT ----------------------

// Arrêter la main
void Hand::Stop() {
	m_velocity = sf::Vector2f(0, 0);
}

// Vérifier si la main touche le sol
bool Hand::IsTouchingGround() {
    return GetPosition().y >= 500; // Ex: Y = 500 est le sol de l'arène
}

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

// Animation Idle (légères oscillations)
void Hand::Idle() {

    if (m_sprite == nullptr) {
        std::cerr << "Erreur: m_sprite est nullptr dans Hand::Idle()" << std::endl;
        return;
    }

    sf::Vector2f currentPosition = GetPosition();
    float amplitude = 10.0f; // Oscillation de 10 pixels
    float speed = 2.0f;      // Fréquence de l'oscillation

}