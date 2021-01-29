#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include <string>

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	SpriteComponent(const SpriteComponent &spriteComponent);
	SpriteComponent(std::string texture);
	SpriteComponent(std::string texture, sf::IntRect rect);
	SpriteComponent(std::string texture, sf::IntRect rect, bool isAnimaton);
	~SpriteComponent();

	sf::Sprite getSprite();
	bool isAnimation();
	void nextAnimationFrame();


	void setPosition(float x, float y);
	bool isEnabled();
	void setEnabled();
	void disable();

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect animationRect;

	int frameWidth;

	bool isAnim = false;
	int animationSpeed = 3;
	int currentAnimationTick = 0;

	int numberOfFrames = 0;
	int currentAnimationFrame = 0;

	bool enabled = true;
};
