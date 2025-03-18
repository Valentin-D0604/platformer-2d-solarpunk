#include "Debug.h"

#include "../Managers/GameManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

Debug* Debug::Get()
{
	static Debug mInstance;

	return &mInstance;
}

void Debug::Draw(sf::RenderWindow* pRenderWindow)
{
	for (Line& line : m_lines)
	{
		pRenderWindow->draw(&line.start, 2, sf::Lines);
	}

	m_lines.clear();

	for (sf::Text& text : m_texts)
	{
		pRenderWindow->draw(text);
	}

	m_texts.clear();

	for (sf::CircleShape& circle : m_circles)
	{
		pRenderWindow->draw(circle);
	}

	m_circles.clear();
}

void Debug::DrawLine(float x1, float y1, float x2, float y2, const sf::Color& color)
{
	Line line;

	line.start = sf::Vertex(sf::Vector2f(x1, y1));
	line.start.color = color;

	line.end = sf::Vertex(sf::Vector2f(x2, y2));
	line.end.color = color;

	Debug::Get()->m_lines.push_back(line);
}

void Debug::DrawRectangle(float x, float y, float width, float height, const sf::Color& color)
{
	DrawLine(x, y, x + width, y, color);
	DrawLine(x + width, y, x + width, y + height, color);
	DrawLine(x + width, y + height, x, y + height, color);
	DrawLine(x, y + height, x, y, color);
}

void Debug::DrawCircle(float x, float y, float radius, const sf::Color& color)
{
	sf::CircleShape circle;

	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(x - radius, y - radius);

	Debug::Get()->m_circles.push_back(circle);
}

void Debug::DrawText(float x, float y, const std::string& text, const sf::Color& color)
{
	DrawText(x, y, text, 0.f, 0.f, color);
}

void Debug::DrawText(float x, float y, const std::string& text, float ratioX, float ratioY, const sf::Color& color)
{
	_ASSERT(ratioX >= 0.f && ratioX <= 1.f);
	_ASSERT(ratioY >= 0.f && ratioY <= 1.f);

	sf::Text sfText;

	sfText.setFont(GameManager::Get()->GetFont());
	sfText.setString(text);
	sfText.setCharacterSize(20);
	sfText.setFillColor(color);
	sfText.setPosition(x, y);

	const sf::FloatRect& bounds = sfText.getLocalBounds();
	sfText.setOrigin(bounds.width * ratioX, bounds.height * ratioY);

	Debug::Get()->m_texts.push_back(sfText);
}
