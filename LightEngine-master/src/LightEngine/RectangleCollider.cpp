#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Debug.h"

RectangleCollider::RectangleCollider(sf::Vector2f _position, sf::Vector2f _size, float _rotation) : m_rotation(_rotation)
{
    m_vertices = new sf::Vector2f[4];
    m_shapeTag = ShapeTag::Rectangle;

    // Définition des sommets par rapport au centre
    sf::Vector2f halfSize = _size / 2.f;
    sf::Vector2f localVertices[4] = {
        {-halfSize.x, -halfSize.y},
        {halfSize.x, -halfSize.y},
        {halfSize.x, halfSize.y},
        {-halfSize.x, halfSize.y}
    };

    // Appliquer la rotation et positionner les sommets
    float angleRad = _rotation * (3.14159265f / 180.f);
    for (int i = 0; i < 4; ++i)
    {
        float x = localVertices[i].x * cos(angleRad) - localVertices[i].y * sin(angleRad);
        float y = localVertices[i].x * sin(angleRad) + localVertices[i].y * cos(angleRad);
        m_vertices[i] = _position + sf::Vector2f(x, y);
    }
}

sf::Vector2f* const RectangleCollider::getVertices() const
{
    sf::Vector2f* vertices = m_vertices;

    return vertices;
}

bool RectangleCollider::isColliding(Collider* _other)
{
    bool colliding = false;
    switch (_other->getShapeTag())
    {
        case ShapeTag::Circle:
        {
            CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
            sf::Vector2f otherPos = otherCast->getPosition();
            float otherRadius = otherCast->getRadius();

            colliding = circleRectangleCollision(otherPos, otherRadius, m_vertices);
        }
        case ShapeTag::Rectangle:
        {
            RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
            sf::Vector2f* const otherVertices = otherCast->getVertices();

            colliding = rectangleCollision(m_vertices, otherVertices);
        }
    }

    return colliding;
}

void RectangleCollider::rotate(float _angle)
{
    float angleRad = _angle * (3.14159265f / 180.f);
    sf::Vector2f center = (m_vertices[0] + m_vertices[2]) / 2.f;

    for (int i = 0; i < 4; ++i)
    {
        sf::Vector2f relative = m_vertices[i] - center;
        float x = relative.x * cos(angleRad) - relative.y * sin(angleRad);
        float y = relative.x * sin(angleRad) + relative.y * cos(angleRad);
        m_vertices[i] = center + sf::Vector2f(x, y);
    }

    m_rotation += _angle;
}

sf::Vector2f RectangleCollider::getPosition(float _ratioX, float _ratioY) const
{
    return m_vertices[0] + (m_vertices[1] - m_vertices[0]) * _ratioX + (m_vertices[3] - m_vertices[0]) * _ratioY;
}

void RectangleCollider::setPosition(sf::Vector2f _pos, float _ratioX, float _ratioY)
{
    sf::Vector2f currentCenter = (m_vertices[0] + m_vertices[2]) / 2.f;

    sf::Vector2f halfSize = (m_vertices[2] - m_vertices[0]) / 2.f;
    sf::Vector2f offset = sf::Vector2f(halfSize.x * (2 * _ratioX - 1), halfSize.y * (2 * _ratioY - 1));

    sf::Vector2f newCenter = _pos + offset;
    sf::Vector2f delta = newCenter - currentCenter + m_offset;

    move(delta);
}

void RectangleCollider::move(sf::Vector2f _delta)
{
    for (int i = 0; i < 4; ++i)
    {
        m_vertices[i] += _delta;
    }
}

void RectangleCollider::update()
{
    if (!m_gizmo)
        return;

    Debug::DrawRectangle(m_vertices[0].x, m_vertices[0].y, m_vertices[2].x - m_vertices[0].x, m_vertices[2].y - m_vertices[0].y, sf::Color::Red);
}
