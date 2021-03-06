#pragma once

#include "EventHandler.h"
#include "AutoList.h"
#include "ComponentBase.h"
#include <string>
#include <vector>
#include "SFML/System.hpp"
#include <algorithm>
#include "RenderComponent.h"
#include "Entity.h"

class AnimationComponent : public ComponentBase, public EventHandler,
	public AutoList<AnimationComponent>
{
public:
	struct Animation
	{
		Animation(const std::string &name, const std::vector<sf::Vector2f>& frames,
			int timeLapse) :
			name{ name }, frames{ frames }, timeLapse{ timeLapse }
		{}
		std::string name;
		std::vector<sf::Vector2f> frames;
		int timeLapse;
	};

	AnimationComponent(Entity* parent) :
		ComponentBase{ parent }, m_timer{ 0 }, m_currentFrame{ 0 },
		m_looping{ false }, m_currentAnimation{ -1 },
		m_ac{ parent->getComponent<RenderComponent>() },
		m_complete{ false }
	{}

	void addAnimation(const std::string& name, const std::vector<sf::Vector2f>& frames,
		int timeLapse)
	{
		m_animations.emplace_back(name, frames, timeLapse);
	}

	void playAnimation(const std::string& name, bool isLooping)
	{
		if (m_currentAnimation != -1 &&
			m_animations[m_currentAnimation].name == name) return;

		auto animIter = std::find_if(std::begin(m_animations),
			std::end(m_animations), [&](const Animation& anim)
			{
				return anim.name == name;
			});
		if (animIter == std::end(m_animations)) return;
		
		auto diff = animIter - std::begin(m_animations);

		m_currentAnimation = diff;
		m_timer = 0;
		m_currentFrame = 0;
		m_looping = isLooping;
		setRenderFrame(m_animations[m_currentAnimation].frames[0]);
		m_complete = false;
	}

	void stopAnimation()
	{
		m_currentAnimation = -1;
		m_complete = true;
	}

	bool complete() const
	{
		return m_complete;
	}

	void tick()
	{
		if (m_currentAnimation == -1) return;
		auto& anim = m_animations[m_currentAnimation];
		m_timer = ++m_timer % anim.timeLapse;
		
		if (m_timer != 0) return;

		m_currentFrame = ++m_currentFrame % anim.frames.size();
		
		if (m_currentFrame != 0)
		{
			setRenderFrame(anim.frames[m_currentFrame]);
			return;
		}

		if (!m_looping)
		{
			m_currentAnimation = -1;
			m_complete = true;
			return;
		}

		setRenderFrame(anim.frames[m_currentFrame]);
	}

private:
	std::vector<Animation> m_animations;
	int m_currentAnimation;
	int m_timer;
	int m_currentFrame;
	bool m_looping;
	bool m_complete;
	RenderComponent* m_ac;

	void setRenderFrame(const sf::Vector2f& position)
	{
		m_ac->setTextureOffset(position.x, position.y);
	}
};