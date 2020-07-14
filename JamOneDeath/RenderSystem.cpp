#include "RenderSystem.h"
#include "RenderComponent.h"
#include "Entity.h"


RenderSystem::RenderSystem(sf::RenderWindow* window) :
	m_window{ window }
{
}

void RenderSystem::execute()
{
	renderEntities();
}

void RenderSystem::renderEntities()
{
	m_window->clear(sf::Color::Black);
	std::map<std::string, sf::VertexArray> dvaMap;
	auto size = AutoList<RenderComponent>::size();

	for (int i = 0; i < size; ++i)
	{
		auto rc = AutoList<RenderComponent>::get(i);

		auto path = rc->texturePath();
		auto parentPosition = rc->parent()->position();
		auto rcPosition = rc->position();
		auto position = parentPosition + rcPosition;
		auto texPosition = rc->textureOffset();
		auto texSize = rc->textureSize();

		// Load texture if missing
		processTexturePath(path);

		// If default, store in default va map
		if (rc->color() == sf::Color::White && 
			rc->rotationAngle() == 0.0f)
		{
			if (dvaMap.find(path) == std::end(dvaMap))
				dvaMap[path] = sf::VertexArray{ sf::PrimitiveType::Quads };
			auto& va = dvaMap[path];

			va.append(sf::Vertex{ position, texPosition });
			va.append(sf::Vertex{ sf::Vector2f{position.x + texSize.x, position.y},
				sf::Vector2f{texPosition.x + texSize.x, texPosition.y} });
			va.append(sf::Vertex{ sf::Vector2f{position.x + texSize.x, position.y + texSize.y},
				sf::Vector2f{texPosition.x + texSize.x, texPosition.y + texSize.y} });
			va.append(sf::Vertex{ sf::Vector2f{position.x, position.y + texSize.y},
				sf::Vector2f{texPosition.x, texPosition.y + texSize.y} });

			continue;
		}

		// New va with relevant modifications
		// (insert code here)
	}

	// Draw default VAs and display final composite

	for (const auto &pr : dvaMap)
	{
		sf::RenderStates states{ &m_textureMap[pr.first] };
		m_window->draw(pr.second, states);
	}

	m_window->display();
}

bool RenderSystem::processTexturePath(const std::string& path)
{
	auto result = m_textureMap.find(path);
	if (result == std::end(m_textureMap))
	{
		m_textureMap[path].loadFromFile(path);
		return true;
	}
	return false;
}