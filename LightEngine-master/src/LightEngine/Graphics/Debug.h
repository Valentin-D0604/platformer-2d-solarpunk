#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class GameManager;

namespace sf
{
	class Color;
	class RenderWindow;
}

struct Line 
{
	sf::Vertex start;
	sf::Vertex end;
};

class Debug
{
	std::vector<Line> m_lines;
	std::vector<sf::Text> m_texts;
	std::vector<sf::CircleShape> m_circles;

	void Draw(sf::RenderWindow* _pRenderWindow);

public:
	static Debug* Get();

	static void DrawLine(float _x1, float _y1, float _x2, float _y2, const sf::Color& _color);
	static void DrawRectangle(float _x, float _y, float _width, float _height, const sf::Color& _color);
	static void DrawCircle(float _x, float _y, float _radius, const sf::Color& _color);
	static void DrawText(float _x, float _y, const std::string& _text, const sf::Color& _color);
	static void DrawText(float _x, float _y, const std::string& _text, float _ratioX, float _ratioY, const sf::Color& _color);

	friend GameManager;
};

