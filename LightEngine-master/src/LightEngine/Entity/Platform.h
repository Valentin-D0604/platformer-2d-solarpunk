#pragma once
#include "../Entity/StaticEntity.h"

class Platform : public StaticEntity {
public:
    void OnInitialize() override;
    Collider* GetCollider() { return m_collider; }
};