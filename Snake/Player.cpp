#include "Player.h"
#include "Game.h"

namespace Snake
{
	void Player::InitPlayer(Player& player, const Game& game)
	{
		player.position = { game.playField[7][7].getPosition().x + 16, game.playField[7][7].getPosition().y + 16 };
		player.SetPlayerDirection(player, PlayerDirection::Right);

		player.snakeHead.setTexture(game.gameUIData.snakeHeadTexture);
		player.snakeHead.setScale(0.7f, 0.7f);
		SetSpriteRelativeOrigin(player.snakeHead, 0.5f, 0.5f);
		player.snakeHead.setPosition(player.position);

		tail.clear();
		/*for (size_t i = 0; i < tail.size(); i++)
		{
			tail.push_back(game.gameUIData.snakeBodyTexture);
		}*/

		prevPosition.push_back({ player.position, player.direction });
	}
		
	void Player::SetPlayerDirection(Player& player, PlayerDirection direction)
	{
		player.direction = direction;
	}
	void Player::UpdatePlayer(Player& player, float deltaTime, Game& game)
	{
		if (TIME_TO_MOVE <= game.movePause) {
			TIME_TO_MOVE += deltaTime;
		}
		else {

			switch (player.direction)
			{
			case PlayerDirection::Right:
				player.position.x += player.speed/* * deltaTime*/;
				break;
			case PlayerDirection::Up:
				player.position.y -= player.speed/* * deltaTime*/;
				break;
			case PlayerDirection::Left:
				player.position.x -= player.speed/* * deltaTime*/;
				break;
			case PlayerDirection::Down:
				player.position.y += player.speed/* * deltaTime*/;
				break;
			}

			prevPosition.resize(tail.size());
			prevPosition.push_back({ player.position, player.direction });

			TIME_TO_MOVE = 0;
			
			if (!tail.empty()) {
				for (size_t i = 0; i < tail.size(); i++)
				{
					tail[i].position = prevPosition[i].position;
					tail[i].sprite.setPosition(prevPosition[i].position);
					switch (prevPosition[i].direction)
					{
					case PlayerDirection::Right:
						tail[i].sprite.setRotation(0.f);
						break;
					case PlayerDirection::Left:
						tail[i].sprite.setRotation((float)PlayerDirection::Left * 90);
						break;
					case PlayerDirection::Up:
						tail[i].sprite.setRotation((float)PlayerDirection::Up * -90);
						break;
					case PlayerDirection::Down:
						tail[i].sprite.setRotation((float)PlayerDirection::Down * -90);
					}
				}
				if (tail.size() > 0) {
					tail[0].sprite.setTexture(game.gameUIData.snakeTailEndTexture);
					
					switch (player.prevPosition[0].direction)
					{
					case PlayerDirection::Right:
						tail[0].sprite.setRotation(2.f * 90);
						break;
					case PlayerDirection::Left:
						tail[0].sprite.setRotation(0.f);
						break;
					case PlayerDirection::Up:
						tail[0].sprite.setRotation((float)PlayerDirection::Up * 90);
						break;
					case PlayerDirection::Down:
						tail[0].sprite.setRotation((float)PlayerDirection::Down * 90);
					}
				}
				for (size_t i = 1; i < tail.size(); i++)
				{
					if (tail.size() > 0 && prevPosition[i].direction != prevPosition[i + 1].direction) {
						tail[i].sprite.setTexture(game.gameUIData.snakeBodyRotationTexture);
						TailSegment::TailRotation tailRotation = PreviousPosition::CheckTailRotation(prevPosition[i], prevPosition[i + 1]);
						switch (tailRotation)
						{
						case Snake::TailSegment::TailRotation::RightUp:
							tail[i].sprite.setRotation(0.f);
							break;
						case Snake::TailSegment::TailRotation::RightDown:
							tail[i].sprite.setRotation(3 * 90);
							break;
						case Snake::TailSegment::TailRotation::UpLeft:
							tail[i].sprite.setRotation(3 * 90);
							break;
						case Snake::TailSegment::TailRotation::UpRight:
							tail[i].sprite.setRotation(2 * 90);
							break;
						case Snake::TailSegment::TailRotation::LeftUp:
							tail[i].sprite.setRotation(1 * 90);
							break;
						case Snake::TailSegment::TailRotation::LeftDown:
							tail[i].sprite.setRotation(2 * 90);
							break;
						case Snake::TailSegment::TailRotation::DownLeft:
							tail[i].sprite.setRotation(0.f);
							break;
						case Snake::TailSegment::TailRotation::DownRight:
							tail[i].sprite.setRotation(1 * 90);
							break;
						case Snake::TailSegment::TailRotation::None:
							tail[i].sprite.setTexture(game.gameUIData.snakeBodyTexture);
							break;
						default:
							break;
						}
					}
					if (prevPosition[i].direction == prevPosition[i + 1].direction) {
						tail[i].sprite.setTexture(game.gameUIData.snakeBodyTexture);
					}
					
				}

			}
			prevPosition.erase(prevPosition.begin());
		}
	}

	void Player::IncreaseTailLenght(Player& player, const Game& game, sf::Vector2f applePosition)
	{
		tail.push_back(game.gameUIData.snakeBodyTexture);
	}

	void Player::DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.snakeHead.setPosition(player.position);
		if (player.direction == PlayerDirection::Right) {
			player.snakeHead.setRotation(0.f);
		}
		else if (player.direction == PlayerDirection::Left) {
			player.snakeHead.setRotation((float)PlayerDirection::Left * 90);
		}
		else if (player.direction == PlayerDirection::Up) {
			player.snakeHead.setRotation((float)PlayerDirection::Up * -90);
		}
		else if (player.direction == PlayerDirection::Down) {
			player.snakeHead.setRotation((float)PlayerDirection::Down * -90);
		}

		for (auto& segment : tail) {
			window.draw(segment.sprite);
		}

		window.draw(player.snakeHead);
	}

	sf::FloatRect Player::GetPlayerCollider(const Player& player)
	{
		return { {player.position.x - (float)PLAYER_SIZE / 2.f, player.position.y - (float)PLAYER_SIZE / 2.f} , {(float)PLAYER_SIZE,(float)PLAYER_SIZE} };
	}

	TailSegment::TailSegment(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setScale(0.7f, 0.7f);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}

	sf::FloatRect TailSegment::GetTailCollider(TailSegment& segment)
	{
		return { {segment.position.x - (float)TAIL_SIZE / 2.f, segment.position.y - (float)TAIL_SIZE / 2.f} , {(float)TAIL_SIZE, (float)TAIL_SIZE} };
	}

	TailSegment::TailRotation PreviousPosition::CheckTailRotation(PreviousPosition& prevPos1, PreviousPosition prevPos2)
	{
		static const std::map <std::pair<PlayerDirection, PlayerDirection>, TailSegment::TailRotation> directionMap = {
			{{PlayerDirection::Right, PlayerDirection::Up}, TailSegment::TailRotation::RightUp},
			{{PlayerDirection::Right, PlayerDirection::Down}, TailSegment::TailRotation::RightDown},
			{{PlayerDirection::Up, PlayerDirection::Right}, TailSegment::TailRotation::UpRight},
			{{PlayerDirection::Up, PlayerDirection::Left}, TailSegment::TailRotation::UpLeft},
			{{PlayerDirection::Left, PlayerDirection::Up}, TailSegment::TailRotation::LeftUp},
			{{PlayerDirection::Left, PlayerDirection::Down}, TailSegment::TailRotation::LeftDown},
			{{PlayerDirection::Down, PlayerDirection::Left}, TailSegment::TailRotation::DownLeft},
			{{PlayerDirection::Down, PlayerDirection::Right}, TailSegment::TailRotation::DownRight}
		};

		auto it = directionMap.find({ prevPos1.direction,prevPos2.direction });
		if (it != directionMap.end()) {
			return it->second;
		}
		return TailSegment::TailRotation::None;
	}

}

