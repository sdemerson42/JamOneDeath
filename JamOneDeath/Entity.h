#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <typeindex>
#include <string>

#include "ComponentBase.h"
#include "SFML/System.hpp"

class Entity
{
public:
	Entity();
	bool active()
	{
		return m_active;
	}
	void setActive(bool value)
	{
		m_active = value;
	}
	unsigned int guid()
	{
		return m_guid;
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
	void addTag(const std::string& tag)
	{
		m_tags.push_back(tag);
	}
	bool hasTag(const std::string& tag)
	{
		auto result = std::find(std::begin(m_tags), std::end(m_tags),
			tag);
		return result != std::end(m_tags);
	}

	//Components

	template<typename T, typename ...Args>
	auto addComponent(Args... args)
	{
		m_components.push_back(std::make_unique<T>(this, args...));
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

	template<typename T>
	std::vector<T*> getComponents()
	{
		auto desiredType = std::type_index{ typeid(T) };
		std::vector<T*> r;
		for (const auto& up : m_components)
		{
			if (std::type_index{ typeid(*up.get()) } == desiredType)
			{
				r.push_back(static_cast<T*>(up.get()));
			}
		}
		return r;
	}

	void activateComponents()
	{
		for (auto& cb : m_components)
		{
			cb->setActive(true);
		}
	}


private:
	unsigned int m_guid;
	bool m_active;
	sf::Vector2f m_position;
	std::vector<std::unique_ptr<ComponentBase>> m_components;
	std::vector<std::string> m_tags;

	static unsigned int s_guidCounter;
};
