#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <string>

namespace sf 
{
	class Shape;
    class Color;
}

class Sprite;
class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i m_Position;
        float m_Distance;
		bool m_IsSet;
    };

protected:
    Sprite* m_sprite;
    sf::Vector2f m_Direction;
	Target m_Target;
    float m_Speed = 0.f;
    bool m_ToDestroy = false;
    int m_Tag = -1;

public:
	bool GoToDirection(int _x, int _y, float _speed = -1.f);
    bool GoToPosition(int _x, int _y, float _speed = -1.f);
    void SetPosition(float _x, float _y, float _ratioX = 0.5f, float _ratioY = 0.5f);
    virtual void Move(float _x, float _y);
	void SetDirection(float _x, float _y, float _speed = -1.f);
	void SetSpeed(float _speed) { m_Speed = _speed; }
	void SetTag(int _tag) { m_Tag = _tag; }

    sf::Vector2f GetPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;
    Sprite* GetSprite() { return m_sprite; }

	bool IsTag(int _tag) const { return m_Tag == _tag; }

    void Destroy();
	bool ToDestroy() const { return m_ToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
    T* CreateEntity();

    virtual void OnAnimationEnd(const std::string& _animationIndex) {};
    virtual void OnFrameChange(const std::string& _animationIndex, int _frame) {};

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
	virtual void OnInitialize() {};
    virtual void OnDestroy() {};
	
private:
    virtual void Update();
    virtual void FixedUpdate();
	void Initialize();

    friend class GameManager;
    friend class ResourceManager;
    friend Scene;
};

#include "Entity.inl"