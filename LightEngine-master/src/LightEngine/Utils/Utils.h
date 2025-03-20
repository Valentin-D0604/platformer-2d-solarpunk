#pragma once

#include <SFML/System/Vector2.hpp>

namespace Utils
{
	bool Normalize(sf::Vector2f& _vector);
	float GetDistance(int _x1, int _y1, int _x2, int _y2);
	float GetDistance(sf::Vector2f _v1, sf::Vector2f _v2);
	float GetAngleDegree(const sf::Vector2f& _v1, const sf::Vector2f& _v2);
	float Clamp(float _value, float _min, float _max);
	float Lerp(float _value, float _target, float _factor);
}