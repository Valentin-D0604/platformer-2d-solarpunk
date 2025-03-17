#pragma once

#include <SFML/Graphics.hpp>
#include "vector"

enum class ShapeTag
{
	circle,
	rectangle
};

struct Side
{
	bool up;
	bool down;
	bool left;
	bool right;
};

class CircleCollider;
class RectangleCollider;

class Collider: public sf::Transformable
{
protected:
	sf::Vector2f m_offset;
	ShapeTag m_shapeTag;
	bool m_gizmo;

	// Circle / Rectangle
	bool CheckVertexInsideCircle(sf::Vector2f* const& _rect, const sf::Vector2f& _circleCenter, float _radius);
	std::pair<sf::Vector2f, sf::Vector2f> FindClosestEdge(sf::Vector2f* const& _rect, const sf::Vector2f& _circleCenter);
	bool CheckEdgeCollision(const sf::Vector2f& _A, const sf::Vector2f& _B, const sf::Vector2f& _circleCenter, float _radius);

	bool CircleRectangleCollision(const sf::Vector2f& _circleCenter, float _radius, sf::Vector2f* const& _rect);

	sf::Vector2f FindClosestPointOnRectangle(const sf::Vector2f& _circleCenter, sf::Vector2f* const& _rect);

	// Circle / Circle
	bool CircleCollision(const sf::Vector2f& _posCircle1, const float& _radCircle1, const sf::Vector2f& _posCircle2, const float& _radCircle2);

	// Rectangle / Rectangle

	void RotateVertices(sf::Vector2f* const& _vertices, float _angle);
	bool RectangleCollision(sf::Vector2f* const& _vertex1, sf::Vector2f* const& _vertex2);

	bool IsShapeTag(ShapeTag _tag) const { return m_shapeTag == _tag; };

public:
	ShapeTag GetShapeTag() const { return m_shapeTag; };

	void SetGizmo(bool _active) { m_gizmo = _active; };

	virtual bool IsColliding(Collider* _other) = 0;
	virtual void SetPosition(sf::Vector2f _pos, float _ratioX = 0.5f, float _ratioY = 0.5f) = 0;
	void SetOffset(sf::Vector2f _pos) { m_offset = _pos; };
	virtual sf::Vector2f GetPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const = 0;
	virtual sf::Vector2f GetSize() const = 0;
	virtual bool GetSide(Collider* _other, Side& _side);
	virtual void Update() = 0;
};

