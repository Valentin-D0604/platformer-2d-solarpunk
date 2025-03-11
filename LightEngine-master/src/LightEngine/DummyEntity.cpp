#include "DummyEntity.h"

#include <iostream>

void DummyEntity::onCollision(Entity* other)
{
	std::cout << "DummyEntity::onCollision" << std::endl;
}