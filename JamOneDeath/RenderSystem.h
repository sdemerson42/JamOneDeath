#pragma once

#include "ISystem.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include "EventHandler.h"

class RenderSystem : public ISystem, public EventHandler
{
public:
	RenderSystem(sf::RenderWindow* window);
	void execute() override;
private:
	sf::RenderWindow* m_window;
	std::map<std::string, sf::Texture> m_textureMap;

	void renderEntities();
	bool processTexturePath(const std::string& path);
};