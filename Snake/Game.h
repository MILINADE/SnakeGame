#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"
#include "Player.h"
#include "Apples.h"
#include "Wall.h"

namespace Snake 
{
	enum class GameState
	{
		MainMenu = 0,
		Play,
		GameOver,
		DifficultyLevel,
		RecordTable,
		Settings,
		Exit,
		PopUpQuestionEnterName,
		PopUpEnterName,
		Pause
	};

	enum class GameDifficulty
	{
		Easy = 0,Easier, Middle, Harder, Hard
	};

	struct PlayersRecordData
	{
		std::string name;
		int record = 0;
	};


	struct Game
	{
		std::vector <GameState> gameState;
		std::vector <GameDifficulty> gameDifficulty;
		std::vector <PlayersRecordData> playersData;
		
		std::vector <std::vector <sf::RectangleShape>> playField;
		//sf::RectangleShape playField[15][15];

		GameUIData gameUIData;

		int rewardSize = 1;

		Player player;
		std::vector <Apple> apple;
		std::vector	 <Wall> wall;

		bool soundOn = true;
		bool effectsOn = true;

		float movePause = PAUSE_TO_MOVE;

		int numApplesEaten = 0;
		int totalNumApplesEaten = 0;

		Game() {
			playField.resize(15, std::vector<sf::RectangleShape>(15));
		}
	};

	void Init(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);

	void StartMainMenu(Game& game);
	void UpdateMainMenu(Game& game);

	void StartRecordTableState(Game& game);
	void UpdateRecordTableState(Game& game);

	void StartDifficultyLevelState(Game& game);
	void UpdateDifficultyLevelState(Game& game);

	void StartPlayState(Game& game);
	void UpdatePlayingState(Game& game, float deltaTime);

	void StartGameOverState(Game& game);
	void UpdateGameOverState(Game& game);

	void StartPauseState(Game& game);
	void UpdatePauseState(Game& game);

	void StartPopUpQuestionEnterNameState(Game& game);
	void UpdatePopUpQuestionEnterNameState(Game& game);

	void StartPopUpEnterNameState(Game& game);
	void UpdatePopUpEnterNameState(Game& game);

	void StartSettingState(Game& game);
	void UpdateSettingState(Game& game);

	void UpdateInput(Game& game,sf::Event& event);

	void SwitchGameState(Game& game, GameState gameState);
	void SwitchGameDifficulty(Game& game, GameDifficulty gameDifficulty);
	GameState CurrentGameState(Game& game);
	GameDifficulty CurrentGameDifficulty(Game& game);
	bool CheckUserPlayerName(Game& game);
}