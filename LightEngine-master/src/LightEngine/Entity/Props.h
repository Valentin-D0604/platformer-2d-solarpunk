#pragma once
#include "Entity.h"

class Props : public Entity
{
public:
    void OnInitialize() override;
    void SetTexture(const char* SpriteSheet, const char* sprite);
};

