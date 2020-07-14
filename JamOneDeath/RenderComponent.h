#pragma once

#include "ComponentBase.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "AutoList.h"
#include "EventHandler.h"

class RenderComponent : public ComponentBase, public AutoList<RenderComponent>,
	public EventHandler
{
public:
	RenderComponent(Entity* parent, const std::string& path, float posX, float posY,
		float offsetX, float offsetY, float sizeX, float sizeY) :
		ComponentBase{ parent }, m_texturePath{ path }, m_position{ posX, posY },
		m_textureOffset{ offsetX, offsetY }, m_textureSize{ sizeX, sizeY }
	{
		m_color = sf::Color::White;
		m_rotationAngle = 0.0f;
	}

	const std::string& texturePath() const
	{
		return m_texturePath;
	}
	const sf::Vector2f& position() const
	{
		return m_position;
	}
	void setPosition(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}
	const sf::Vector2f& textureOffset() const
	{
		return m_textureOffset;
	}
	void setTextureOffset(float x, float y)
	{
		m_textureOffset.x = x;
		m_textureOffset.y = y;
	}
	const sf::Vector2f& textureSize() const
	{
		return m_textureSize;
	}
	void setTextureSize(float x, float y)
	{
		m_textureSize.x = x;
		m_textureSize.y = y;
	}
	const sf::Color& color() const
	{
		return m_color;
	}
	void setColor(const sf::Color& color)
	{
		m_color = color;
	}
	float rotationAngle() const
	{
		return m_rotationAngle;
	}
	void setRotationAngle(float value)
	{
		m_rotationAngle = value;
	}
private:
	std::string m_texturePath;
	sf::Vector2f m_position;
	sf::Vector2f m_textureOffset;
	sf::Vector2f m_textureSize;
	sf::Color m_color;
	float m_rotationAngle;
};
