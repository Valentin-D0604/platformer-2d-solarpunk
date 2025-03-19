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
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
    m_collider = new RectangleCollider(pos, { 10,10 });

    m_animationIndex = 0;
    m_frameTimer = 0.0f;

	m_isVulnerable = false;
	m_isSweeping = false;
	m_isGroundSmashing = false;
	m_isThrowing = false;

    if (m_isLeft) {
        idlePositions = { {89,304}, {91,300}, {99,294}, {108,289}, {113,287}, {115,287}, {113,291}, {105,294}, {99,300} };
        groundSmashPositions = { {169,271}, {168,254}, {170,203}, {172,170}, {173,157}, {174,161}, {174,166}, {172,179}, {181,227}, {175,289} };
        throwPositions = { {159,142}, {157,144}, {152,152}, {147,162}, {138,175}, {129,199}, {130,255}, {180,347}, {194,353}, {160,325}, {174,321}, {182,315}, {184,317}, {184,321}, {182,322}, {182,320}, {182,294}, {186,247}, {187,222} };
        sweepPositions = { {169,312}, {169,312}, {168,314}, {165,313}, {168,316}, {172,314}, {183,314}, {203,317}, {229,319}, {240,321} };
    }
    else {
        idlePositions = { {411,302}, {407,298}, {401,293}, {394,288}, {386,284}, {386,285}, {389,288}, {393,293}, {402,299} };
        groundSmashPositions = { {327,271}, {328,253}, {326,204}, {326,171}, {325,156}, {324,160}, {323,165}, {321,178}, {321,226}, {322,288} };
        throwPositions = { {293,346}, {296,343}, {299,339}, {305,330}, {318,313}, {334,295}, {348,271}, {336,215}, {331,206}, {336,299}, {317,314}, {314,318}, {314,321}, {314,322}, {314,324}, {316,321}, {316,296}, {315,246}, {314,221} };
        sweepPositions = { {329,312}, {331,312}, {336,312}, {334,311}, {328,310}, {302,305}, {268,307}, {246,312}, {240,317}, {240,321} };
    }
}

// Mise à jour des actions de la main
void Hand::OnUpdate() {
    if (m_isSweeping) {
        Sweep();
        PlayAnimation(sweepPositions);
    }
    else if (m_isGroundSmashing) {
        GroundSmash();
        PlayAnimation(groundSmashPositions);
    }
    else if (m_isThrowing) {
        ThrowRock();
        PlayAnimation(throwPositions);
    }
    else if (m_isVulnerable) {
        HandleStun();
        PlayAnimation(idlePositions);
    }
    else {
        Idle();
		PlayAnimation(idlePositions);
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

// Fonction pour jouer une animation en lisant les positions
void Hand::PlayAnimation(const std::vector<sf::Vector2f>& positions) {
    m_frameTimer += GetDeltaTime();

    if (m_frameTimer >= FRAME_DURATION) {
        m_frameTimer = 0.0f;
        m_animationIndex++;

        if (m_animationIndex >= positions.size()) {
            m_animationIndex = 0; // Boucle sur l'animation
        }
    }

    SetPosition(positions[m_animationIndex].x, positions[m_animationIndex].y);
}

// Animation Idle (légères oscillations)
void Hand::Idle() {

    if (m_sprite == nullptr) {
        std::cerr << "Erreur: m_sprite est nullptr dans Hand::Idle()" << std::endl;
        return;
    }

    float amplitude = 10.0f; // Oscillation de 10 pixels
    float speed = 2.0f;      // Fréquence de l'oscillation
    if (this != nullptr)
        SetPosition(200, 300); // Position neutre
}