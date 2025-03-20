#pragma once
#include "../Entity/StaticEntity.h"

class Platform : public StaticEntity {
public:
    void OnInitialize() override;
    void SetTexture(const char* SpriteSheet, const char* sprite);
    Collider* GetCollider() { return m_collider; }
};