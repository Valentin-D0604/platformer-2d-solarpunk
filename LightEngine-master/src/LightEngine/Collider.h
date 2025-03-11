#pragma once

#include <SFML/Graphics.hpp>
#include "vector"

enum class ShapeTag
{
	Circle,
	Rectangle
};

class CircleCollider;
class RectangleCollider;

class Collider: public sf::Transformable
{
protected:
	sf::Vector2f m_offset;
	ShapeTag m_shapeTag;

	// Circle / Rectangle
	bool checkVertexInsideCircle(sf::Vector2f* const& _rect, const sf::Vector2f& _circleCenter, float _radius);
	std::pair<sf::Vector2f, sf::Vector2f> findClosestEdge(sf::Vector2f* const& _rect, const sf::Vector2f& _circleCenter);
	bool checkEdgeCollision(const sf::Vector2f& _A, const sf::Vector2f& _B, const sf::Vector2f& _circleCenter, float _radius);

	bool circleRectangleCollision(const sf::Vector2f& _circleCenter, float _radius, sf::Vector2f* const& _rect);

	sf::Vector2f findClosestPointOnRectangle(const sf::Vector2f& circleCenter, sf::Vector2f* const& rect);

	// Circle / Circle
	bool circleCollision(const sf::Vector2f& _posCircle1, const float& _radCircle1, const sf::Vector2f& _posCircle2, const float& _radCircle2);

	// Rectangle / Rectangle

	void rotateVertices(sf::Vector2f* const& _vertices, float _angle);
	bool rectangleCollision(sf::Vector2f* const& _vertex1, sf::Vector2f* const& _vertex2);

	bool isShapeTag(ShapeTag _tag) const { return m_shapeTag == _tag; };

public:
	ShapeTag getShapeTag() const { return m_shapeTag; };

	virtual bool isColliding(Collider* _other) = 0;
	virtual void setPosition(sf::Vector2f _pos, float _ratioX = 0.5f, float _ratioY = 0.5f) = 0;
	void setOffset(sf::Vector2f _pos) { m_offset = _pos; };
	virtual sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const = 0;
	virtual sf::Vector2f getGlobalPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const = 0;
};

