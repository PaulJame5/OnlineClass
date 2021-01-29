#pragma once
#include "I_ComponentSystem.h"
#include "SmallDotComponent.h"
#include <SFML/Audio.hpp>


class SmallDotSystem : public I_ComponentSystem<SmallDotComponent>
{
public:
	SmallDotSystem();
	~SmallDotSystem();
	void update(sf::Sound sound[]);
	void update() override;
	void restart();

private:

};