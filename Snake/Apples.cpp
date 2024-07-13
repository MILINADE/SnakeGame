#include "Apples.h"
#include "Game.h"

namespace Snake
{
	void Apple::Init(const Game& game)
	{
		sprite.setTexture(game.gameUIData.appleTexture);
		sprite.setScale(0.5f, 0.5f);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}
	void Apple::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
	void Apple::SetPosition(const sf::Vector2f& position)
	{
		this->position = position;
		sprite.setPosition(position);
	}
	sf::FloatRect Apple::GetAppleCollider(Apple& apple)
	{
		return { {apple.position.x - (float)APPLE_SIZE / 2.f, apple.position.y - (float)APPLE_SIZE / 2.f} , {(float)APPLE_SIZE, (float)APPLE_SIZE} };
	}
}