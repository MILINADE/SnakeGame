#pragma once
#include <SFML\Graphics.hpp>

namespace Snake 
{
	struct Game;

	struct Wall
	{
		sf::Vector2f position;
		sf::Sprite sprite;

		void Init(const Game& game);
		void Draw(sf::RenderWindow& window);
		void SetPosition(const sf::Vector2f& position);
		sf::FloatRect GetWallCollider(Wall& wall);
	};
}