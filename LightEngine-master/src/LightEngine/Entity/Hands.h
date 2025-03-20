#pragma once

#include "Boss.h"
#include "PhysicsEntity.h"
#include "../Utils/StateMachine.h"

class Boss;

class Hand : public PhysicsEntity {
private:
    Boss* m_owner;
	bool m_isLeft;
    int m_animationIndex;
    float m_frameTimer;
    const float FRAME_DURATION = 0.1f;
    float m_timer = 0.0f;

public:

    void OnInitialize() override;
	void PositionSettings(std::vector<sf::Vector2f> _idlePositions, std::vector<sf::Vector2f> _groundSmashPositions, std::vector<sf::Vector2f> _grabRockPosition, std::vector<sf::Vector2f> _throwPositions, std::vector<sf::Vector2f> _retreatPositions);
    void OnUpdate() override;
    void OnCollision(Entity* _collidedWith) override; 

    void PlayAnimation(const std::vector<sf::Vector2f> positions);
	
    void SetOwner(Boss* _owner);
    Boss* GetOwner() { return m_owner; }
    
    std::vector<sf::Vector2f> idlePositions;
    std::vector<sf::Vector2f> groundSmashPositions;
    std::vector<sf::Vector2f> grabRockPosition;
    std::vector<sf::Vector2f> throwPositions;
	std::vector<sf::Vector2f> retreatPositions;

private:
    friend class Boss;
};