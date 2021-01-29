#pragma once
#include "I_ComponentSystem.h"
#include "InputComponent.h"
#include <SFML/Graphics.hpp>


class InputSystem : public I_ComponentSystem<InputComponent>
{
public:
	InputSystem();
	~InputSystem();

	void update() override;

	void inputCheck(sf::Event& event);
	void inputLetGoCheck(sf::Event& event);
private:
};