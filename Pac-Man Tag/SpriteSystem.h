#pragma once
#include "I_ComponentSystem.h"
#include "SpriteComponent.h"


class SpriteSystem : public I_ComponentSystem<SpriteComponent>
{
public:
	SpriteSystem();
	~SpriteSystem();

	void update() override;
	static void drawSprites(sf::RenderWindow& window);
	static void animate();
	void restart();
private:

};