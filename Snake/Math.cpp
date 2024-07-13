#include "Math.h"
#include "Game.h"

namespace Snake
{
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * (float)spriteRect.width, originY * (float)spriteRect.height);
	}
	sf::Vector2f GetRandomPosition(Game& game)
	{
		int col = rand() % 15;
		int row = rand() % 15;
		return game.playField[row][col].getPosition() + sf::Vector2f(16,16);
	}
	bool DoShapeCollide(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
	{
		return rect1.getPosition().x < rect2.getPosition().x + rect2.getSize().x &&
			rect1.getPosition().x + rect1.getSize().x > rect2.getPosition().x &&
			rect1.getPosition().y < rect2.getPosition().y + rect2.getSize().y &&
			rect1.getPosition().y + rect1.getSize().y > rect2.getPosition().y;
	}
	sf::FloatRect GetWindowCollide()
	{
		return { {480 / 2.f - (float)448 / 2.f, 480 / 2.f + 50 - (float)448 / 2.f} , {(float)448, (float)448} };
	}
}


