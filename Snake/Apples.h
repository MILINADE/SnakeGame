#pragma once
#include <SFML\Graphics.hpp>

namespace Snake
{
	struct Game;

	struct Apple
	{
		sf::Vector2f position;
		sf::Sprite sprite;
		bool isAppleEaten = false;

		void Init(const Game& game);
		void Draw(sf::RenderWindow& window);
		void SetPosition(const sf::Vector2f& position);
		sf::FloatRect GetAppleCollider(Apple& apple);
	};
}