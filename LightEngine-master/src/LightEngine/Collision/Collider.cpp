#include "Collider.h"
#include "../Utils/Utils.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "../Managers/Managers.h"

bool Collider::CheckVertexInsideCircle(sf::Vector2f* const& _rect, const sf::Vector2f& _circleCenter, float _radius) {
    for (int i = 0; i < 4; i++)
    {
        if (Utils::GetDistance(_rect[i], _circleCenter) <= _radius)
            return true;
    }
    return false;
}

std::pair<sf::Vector2f, sf::Vector2f> Collider::FindClosestEdge(sf::Vector2f* const& _rect, const sf::Vector2f& _circleCenter)
{
    float minDistance = std::numeric_limits<float>::max();
    std::pair<sf::Vector2f, sf::Vector2f> closestEdge;

    for (size_t i = 0; i < 4; ++i)
    {
        sf::Vector2f p1 = _rect[i];
        sf::Vector2f p2 = _rect[(i + 1) % 4];

        sf::Vector2f edge = p2 - p1;
        sf::Vector2f edgeDir = edge / std::sqrt(edge.x * edge.x + edge.y * edge.y);

        sf::Vector2f p1ToCenter = _circleCenter - p1;
        float projection = (p1ToCenter.x * edgeDir.x + p1ToCenter.y * edgeDir.y);
        sf::Vector2f closestPoint = p1 + projection * edgeDir;

        if (projection < 0)
            closestPoint = p1;
        else if (projection > std::sqrt(edge.x * edge.x + edge.y * edge.y))
            closestPoint = p2;

        float dist = std::sqrt((closestPoint.x - _circleCenter.x) * (closestPoint.x - _circleCenter.x) +
            (closestPoint.y - _circleCenter.y) * (closestPoint.y - _circleCenter.y));

        if (dist < minDistance)
        {
            minDistance = dist;
            closestEdge = { p1, p2 };
        }
    }

    return closestEdge;
}

bool Collider::CheckEdgeCollision(const sf::Vector2f& _A, const sf::Vector2f& _B, const sf::Vector2f& _circleCenter, float _radius) {

    sf::Vector2f AB = { _B.x - _A.x, _B.y - _A.y };
    sf::Vector2f AC = { _circleCenter.x - _A.x, _circleCenter.y - _A.y };

    float ab2 = AB.x * AB.x + AB.y * AB.y;
    float ac_ab = AC.x * AB.x + AC.y * AB.y;
    float t = ac_ab / ab2;

    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;

    sf::Vector2f closest = { _A.x + t * AB.x, _A.y + t * AB.y };

    return Utils::GetDistance(closest, _circleCenter) <= _radius;
}

bool Collider::CircleRectangleCollision(const sf::Vector2f& _circleCenter, float _radius, sf::Vector2f* const& _rect) {
    if (Collider::CheckVertexInsideCircle(_rect, _circleCenter, _radius))
        return true;

    for (size_t i = 0; i < 4; ++i)
    {
        sf::Vector2f A = _rect[i];
        sf::Vector2f B = _rect[(i + 1) % 4];

        if (Collider::CheckEdgeCollision(A, B, _circleCenter, _radius))
            return true;
    }

    return false;
}

sf::Vector2f Collider::FindClosestPointOnRectangle(const sf::Vector2f& _circleCenter, sf::Vector2f* const& _rect)
{
    sf::Vector2f closestPoint;
    float minDistance = std::numeric_limits<float>::max();

    for (size_t i = 0; i < 4; ++i)
    {
        sf::Vector2f A = _rect[i];
        sf::Vector2f B = _rect[(i + 1) % 4];

        sf::Vector2f edge = B - A;
        float edgeLength = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        sf::Vector2f edgeDir = edge / edgeLength;

        sf::Vector2f AToCenter = _circleCenter - A;
        float projection = (AToCenter.x * edgeDir.x + AToCenter.y * edgeDir.y);

        sf::Vector2f pointOnEdge = A + projection * edgeDir;

        if (projection < 0) pointOnEdge = A;
        else if (projection > edgeLength) pointOnEdge = B;

        float dist = Utils::GetDistance(_circleCenter, pointOnEdge);
        if (dist < minDistance)
        {
            minDistance = dist;
            closestPoint = pointOnEdge;
        }
    }

    return closestPoint;
}

bool Collider::CircleCollision(const sf::Vector2f& _posCircle1, const float& _radCircle1, const sf::Vector2f& _posCircle2, const float& _radCircle2)
{
    float distance = Utils::GetDistance(_posCircle1, _posCircle2);

    if (distance < _radCircle1 + _radCircle2)
        return true;

    return false;
}

void Collider::RotateVertices(sf::Vector2f* const& _vertices, float _angle)
{
    sf::Vector2f center = (_vertices[0] + _vertices[2]) * 0.5f;

    // Conversion de l'angle en radians
    float radians = _angle * (3.14159265f / 180.0f);
    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);

    for (int i = 0; i < 4; i++)
    {
        sf::Vector2f translated = _vertices[i] - center;
        _vertices[i].x = center.x + translated.x * cosTheta - translated.y * sinTheta;
        _vertices[i].y = center.y + translated.x * sinTheta + translated.y * cosTheta;
    }
}

bool Collider::RectangleCollision(sf::Vector2f* const& _vertices1, sf::Vector2f* const& _vertices2)
{
    std::vector<sf::Vector2f> axes;

    for (int i = 0; i < 4; ++i)
    {
        sf::Vector2f edge = { _vertices1[(i + 1) % 4].x - _vertices1[i].x, _vertices1[(i + 1) % 4].y - _vertices1[i].y };
        axes.push_back({ -edge.y, edge.x });
    }

    for (int i = 0; i < 4; ++i)
    {
        sf::Vector2f edge = { _vertices2[(i + 1) % 4].x - _vertices2[i].x, _vertices2[(i + 1) % 4].y - _vertices2[i].y };
        axes.push_back({ -edge.y, edge.x });
    }

    for (const sf::Vector2f& axis : axes) {
        float min1 = INFINITY, max1 = -INFINITY;
        float min2 = INFINITY, max2 = -INFINITY;

        for (int i = 0; i < 4; i++)
        {
            // vertices 1
            float proj1 = _vertices1[i].x * axis.x + _vertices1[i].y * axis.y;
            min1 = std::min(min1, proj1);
            max1 = std::max(max1, proj1);

            // vertices 2
            float proj2 = _vertices2[i].x * axis.x + _vertices2[i].y * axis.y;
            min2 = std::min(min2, proj2);
            max2 = std::max(max2, proj2);
        }

        if (max1 < min2 || max2 < min1)
            return false;

    }

    return true;
}
#include <iostream>

bool Collider::GetSide(Collider* _other, Side& _side)
{
    if (_other->GetShapeTag() != ShapeTag::rectangle)
        return false;

   // std::cout << "Other left: " << _other->GetPosition(0, 0).x << " (>=) " << "This Right: " << GetPosition(1, 0).x << std::endl;
    //std::cout << "Other Right: " << _other->GetPosition(1, 0).x << " (<=) " << "This left: " << GetPosition(0, 0).x << std::endl;
    if (_other->GetPosition(0, 0).x >= GetPosition(1, 0).x)
    {
        _side.left |= true;
        _side.right |= false;
        std::cout << _side.left << std::endl;
    }
    else if (_other->GetPosition(1, 0).x <= GetPosition(0, 0).x)
    {
        _side.left |= false;
        _side.right |= true;
        std::cout << _side.right << std::endl;
    }

    else
    {
        _side.left |= false;
        _side.right |= false;
    }

    if (_other->GetPosition(0, 0).y >= GetPosition(0, 1).y)
    {
        _side.up |= true;
        _side.down |= false;
    }

    else if (_other->GetPosition(0, 1).y <= GetPosition(0, 0).y)
    {
        _side.up |= false;
        _side.down |= true;
    }

    else
    {
        _side.up |= false;
        _side.down |= false;
    }

    return true;
}