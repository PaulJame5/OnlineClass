#include "SpriteSystem.h"

SpriteSystem::SpriteSystem()
{
}

SpriteSystem::~SpriteSystem()
{
}

void SpriteSystem::update()
{
	std::map<int, std::vector<SpriteComponent> >::iterator it = SpriteSystem::getEntities().begin();

	for (; it != SpriteSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			it->second.at(i).nextAnimationFrame();
		}

	}
}

void SpriteSystem::drawSprites(sf::RenderWindow& window)
{
	std::map<int, std::vector<SpriteComponent> >::iterator it = SpriteSystem::getEntities().begin();

	for (; it != SpriteSystem::getEntities().end(); ++it)
	{
		int numberOfComponents = it->second.size();

		for (int i = 0; i < numberOfComponents; i++)
		{
			if (it->second.at(i).isEnabled() == false)
			{
				continue;
			}
			window.draw(it->second.at(i).getSprite());
		}

	}
}

void SpriteSystem::animate()
{
	
}
