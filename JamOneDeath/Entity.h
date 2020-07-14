#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <typeindex>

#include "ComponentBase.h"
#include "SFML/System.hpp"

class Entity
{
public:
	bool active()
	{
		return m_active;
	}
	void setActive(bool value)
	{
		m_active = value;
	}
	const sf::Vector2f& position()
	{
		return m_position;
	}
	void setPosition(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}
	void setPosition(const sf::Vector2f& position)
	{
		m_position = position;
	}
	void addPosition(float x, float y)
	{
		m_position.x += x;
		m_position.y += y;
	}
	void addPosition(const sf::Vector2f& position)
	{
		m_position += position;
	}

	//Components

	template<typename T, typename ...Args>
	auto addComponent(Args... args)
	{
		m_components.push_back(std::make_unique<T>(args...));
		return static_cast<T*>(m_components.back().get());
	}

	template<typename T>
	T* getComponent()
	{
		auto desiredType = std::type_index{ typeid(T) };
		auto result = std::find_if(std::begin(m_components), std::end(m_components),
			[&](const std::unique_ptr<ComponentBase>& up)
			{
				return std::type_index{ typeid(*up.get()) } == desiredType;
			});
		if (result != std::end(m_components))
			return static_cast<T*>(result->get());
		return nullptr;
	}


private:
	bool m_active;
	sf::Vector2f m_position;
	std::vector<std::unique_ptr<ComponentBase>> m_components;
	
};