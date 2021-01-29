#include "SpriteComponent.h"
#include <iostream>
SpriteComponent::SpriteComponent()
{
}

SpriteComponent::SpriteComponent(const SpriteComponent& spriteComponent)
{
	texture = spriteComponent.texture;
	sprite = spriteComponent.sprite;
	isAnim = spriteComponent.isAnim;
	numberOfFrames = spriteComponent.numberOfFrames;
	animationRect = spriteComponent.animationRect;
	frameWidth = spriteComponent.frameWidth;
	enabled = true;
}

SpriteComponent::SpriteComponent(std::string texture)
{
	if (!this->texture.loadFromFile(texture))
	{
		std::cout << "Cannot find file " << texture << std::endl;
	}
	sprite.setTexture(this->texture);
	sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	isAnim = false;
	frameWidth = 0;
	enabled = true;
}

SpriteComponent::SpriteComponent(std::string texture, sf::IntRect rect)
{
	if (!this->texture.loadFromFile(texture))
	{
		std::cout << "Cannot find file " << texture << std::endl;
	}
	sprite.setTexture(this->texture);
	sprite.setTextureRect(rect);
	sprite.setOrigin(rect.width / 2, rect.height / 2);
	isAnim = false;
	frameWidth = 0;
	enabled = true;
}

SpriteComponent::SpriteComponent(std::string texture, sf::IntRect rect, bool isAnim)
{
	if (!this->texture.loadFromFile(texture))
	{
		std::cout << "Cannot find file " << texture << std::endl;
	}
	sprite.setTexture(this->texture);
	sprite.setTextureRect(rect);
	sprite.setOrigin(rect.width / 2, rect.height / 2);
	this->isAnim = isAnim;

	if (isAnim)
	{
		numberOfFrames =  (int)(this->texture.getSize().x / rect.width);
	}
	animationRect = rect;
	frameWidth = animationRect.width;
	enabled = true;
}

SpriteComponent::~SpriteComponent()
{
}

sf::Sprite SpriteComponent::getSprite()
{
	return sprite;
}

bool SpriteComponent::isAnimation()
{
	return isAnim;
}

void SpriteComponent::nextAnimationFrame()
{
	if (currentAnimationTick != animationSpeed)
	{
		currentAnimationTick++;
		return;
	}

	currentAnimationTick = 0;

	currentAnimationFrame++;
	if (currentAnimationFrame >= numberOfFrames)
	{
		currentAnimationFrame = 0; 
	}

	animationRect.left = (frameWidth * currentAnimationFrame);

	sprite.setTextureRect(animationRect);

}

void SpriteComponent::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

bool SpriteComponent::isEnabled()
{
	return enabled;
}

void SpriteComponent::setEnabled()
{
	enabled = true;
}

void SpriteComponent::disable()
{
	enabled = false;
}
