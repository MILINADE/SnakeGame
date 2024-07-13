#pragma once
#include <SFML/Graphics.hpp>

namespace Snake
{
	struct Game;

	struct Rectangle
	{
		sf::Vector2f position;
		sf::Vector2f size;
	};

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	sf::Vector2f GetRandomPosition(Game& game);
	bool DoShapeCollide(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
	sf::FloatRect GetWindowCollide();
}