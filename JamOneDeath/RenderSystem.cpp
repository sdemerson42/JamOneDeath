#include "RenderSystem.h"
#include "RenderComponent.h"
#include "Entity.h"
#include "Globals.h"

RenderSystem::RenderSystem(sf::RenderWindow* window) :
	m_window{ window }
{
	m_tileTexture.loadFromFile("GFX/Test.png");
	registerFunc(this, &RenderSystem::onSetTilemapEvent);
}

void RenderSystem::execute()
{
	m_window->clear(sf::Color::Black);
	renderTilemap();
	renderEntities();
}

void RenderSystem::renderTilemap()
{
	sf::VertexArray va{ sf::PrimitiveType::Quads };
	sf::RenderStates states{ &m_tileTexture };

	int xSize = m_tilemapEvent.tilemap->size();
	int ySize = (*m_tilemapEvent.tilemap)[0].size();

	for (int i = 0; i < xSize; ++i)
	{
		for (int j = 0; j < ySize; ++j)
		{
			float xPos = (float)(i * Globals::tileWidth);
			float yPos = (float)(j * Globals::tileHeight);
			float txPos = (float)((*m_tilemapEvent.tilemap)[i][j] * Globals::tileWidth);
			float tyPos = 0.0f;

			va.append(sf::Vertex{ sf::Vector2f{xPos, yPos}, 
				sf::Vector2f{txPos, tyPos } });
			va.append(sf::Vertex{ sf::Vector2f{xPos + Globals::tileWidth, yPos},
				sf::Vector2f{txPos + Globals::tilemapWidth, tyPos } });
			va.append(sf::Vertex{ sf::Vector2f{xPos + Globals::tileWidth, yPos + Globals::tileHeight},
				sf::Vector2f{txPos + Globals::tilemapWidth, tyPos + Globals::tileHeight } });
			va.append(sf::Vertex{ sf::Vector2f{xPos, yPos + Globals::tileHeight},
				sf::Vector2f{txPos, tyPos + Globals::tileHeight } });
		}
	}
	m_window->draw(va, states);
}

void RenderSystem::renderEntities()
{
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

void RenderSystem::onSetTilemapEvent(const SetTilemapEvent* event)
{
	m_tilemapEvent = *event;
}