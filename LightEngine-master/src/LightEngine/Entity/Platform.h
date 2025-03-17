#pragma once
#include "../Entity/StaticEntity.h"

class Platform : public StaticEntity {
public:
    void OnInitialize() override;
};