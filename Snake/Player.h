#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace Snake
{
	enum class PlayerDirection : int
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Game;

	struct TailSegment
	{
		sf::Vector2f position;
		sf::Sprite sprite;

		TailSegment(const sf::Texture& texture);
		sf::FloatRect GetTailCollider(TailSegment& segment);

		enum class TailRotation : int
		{
			RightUp = 0, RightDown,
			UpLeft, UpRight,
			LeftUp,LeftDown,
			DownLeft, DownRight,
			None
		};
	};

	struct PreviousPosition
	{
		sf::Vector2f position;
		PlayerDirection direction = PlayerDirection::Right;

		static TailSegment::TailRotation CheckTailRotation(PreviousPosition& prevPos1, PreviousPosition prevPos2);
	};

	struct Player
	{
		float speed = STEP_DISTANCE;

		sf::Vector2f position;
		sf::Sprite snakeHead;
		PlayerDirection direction = PlayerDirection::Right;

		std::vector <TailSegment> tail;
		std::vector <PreviousPosition> prevPosition;

		void InitPlayer(Player& player, const Game& game);
		void SetPlayerDirection(Player& player, PlayerDirection direction);
		void UpdatePlayer(Player& player, float deltaTime, Game& game);
		void DrawPlayer(Player& player, sf::RenderWindow& window);
		void IncreaseTailLenght(Player& player, const Game& game, sf::Vector2f applePosition);
		sf::FloatRect GetPlayerCollider(const Player& player);
	};


}