#include <SFML/System/Vector2.hpp>

#include <cmath>
#include "Utils.h"

namespace Utils 
{
    bool Normalize(sf::Vector2f& vector)
    {
        float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude != 0)
		{
			vector.x /= magnitude;
			vector.y /= magnitude;
		
			return true;
		}

		return false;
    }

	float GetDistance(int x1, int y1, int x2, int y2)
	{
		int x = x2 - x1;
		int y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}

	float GetDistance(sf::Vector2f _v1, sf::Vector2f _v2)
	{
		int x = _v2.x - _v1.x;
		int y = _v2.y - _v1.y;

		return std::sqrt(x * x + y * y);
	}

	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		float dot = v1.x * v2.x + v1.y * v2.y;
		float det = v1.x * v2.y - v1.y * v2.x;

		return std::atan2(det, dot) * 180 / 3.14159265;
	}
	float Clamp(float _value, float _min, float _max)
	{
		_value = _value < _min ? _min : _value;
		_value = _value > _max ? _max : _value;

		return _value;
	}
}