#include "Wall.h"
#include "Game.h"

namespace Snake
{
	void Wall::Init(const Game& game)
	{
		sprite.setTexture(game.gameUIData.wallTexture);
		sprite.setScale(0.06f,0.06f);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}
	void Wall::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
	void Wall::SetPosition(const sf::Vector2f& position)
	{
		this->position = position;
		sprite.setPosition(position);
	}
	sf::FloatRect Wall::GetWallCollider(Wall& wall)
	{
		return { {wall.position.x - (float)WALL_SIZE / 2.f, wall.position.y - (float)WALL_SIZE / 2.f} , {(float)WALL_SIZE, (float)WALL_SIZE} };
	}
}
