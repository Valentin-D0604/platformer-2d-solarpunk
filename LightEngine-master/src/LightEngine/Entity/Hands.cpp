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
	m_isVulnerable = false;
	m_isSweeping = false;
	m_isGroundSmashing = false;
	m_isThrowing = false;
}


Hand::Hand(bool isLeft) : m_isLeft(isLeft) {}

// Mise à jour des actions de la main
void Hand::OnUpdate() {
    if (m_isSweeping) {
        Sweep();
    }
    else if (m_isGroundSmashing) {
        GroundSmash();
    }
    else if (m_isThrowing) {
        ThrowRock();
    }
    else if (m_isVulnerable) {
        HandleStun();
    }
    else {
        Idle();
    }
}

// Détection de collision (ex: le projectile spécial qui stun la main)
void Hand::OnCollision(Entity* _collidedWith) {
    if (_collidedWith->IsTag(TestScene::Tag::bullet)) {
        Stun();
    }
}

// ----------------------  LOGIQUE ACTIONS ----------------------

void Hand::Sweep() {
    // Mouvement de balayage de gauche à droite
    float sweepSpeed = 300.0f;  // Vitesse de balayage
    if (m_isLeft) {
        m_velocity = sf::Vector2f(sweepSpeed, 0); // Balayage vers la droite
    }
    else {
        m_velocity = sf::Vector2f(-sweepSpeed, 0); // Balayage vers la gauche
    }

    // Réduction progressive de la vitesse pour terminer l'attaque
    m_timer -= GetDeltaTime();
    if (m_timer <= 0) {
        Stop();
        m_isSweeping = false;
    }
}

void Hand::GroundSmash() {
    // Descente rapide vers le sol
    float smashSpeed = 500.0f;
    m_velocity = sf::Vector2f(0, smashSpeed); // Descente

    // Vérifier si la main touche le sol
    if (IsTouchingGround()) {
        Stop(); // Arrêter la descente
        m_isGroundSmashing = false;
        PickUpRock(); // Ramasser un rocher
    }
}

void Hand::PickUpRock() {
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

// Animation Idle (légères oscillations)
void Hand::Idle() {
    float amplitude = 10.0f; // Oscillation de 10 pixels
    float speed = 2.0f;      // Fréquence de l'oscillation
    SetPosition(GetPosition().x, 400 + amplitude * sin(GetDeltaTime() * speed));
}