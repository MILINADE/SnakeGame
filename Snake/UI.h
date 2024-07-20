#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include <vector>

namespace Snake
{
	struct Button
	{
		sf::Text buttonText;
		sf::Vector2f position;
		bool isActive = false;

		void Init(const std::string& text, sf::Font& font, int characterSize, const sf::Vector2f& position);
		void Draw(sf::RenderWindow& window);
		void ChangeColor(sf::Color color);
		void SetActive(bool active);

		bool IsActive() const;
	};

	struct Game;

	struct PlayState
	{
		sf::Sprite numAppleUI;
		sf::Sprite totalNumApplesSprite;
		sf::Text numEatenAppleText;
		sf::Text totalNumApplesText;
		sf::Text timeToStartMove;
		sf::Music playStateMusic;
		sf::SoundBuffer coinUpBuffer;
		sf::Sound coinUp;
		sf::SoundBuffer endGameBuffer;
		sf::Sound endGame;

		void DrawPlayState(Game& game, sf::RenderWindow& window);
	};

	struct MainMenuState
	{
		sf::Music mainMenuMusic;

		void DrawMainMenu(Game& game, sf::RenderWindow& window);
	};

	struct SettingsState
	{
		sf::Text settingsText;
		std::vector <Button> settingsButtons;
		sf::Text soundOntext;
		sf::Text effectsOntext;

		void DrawSettingsState(Game& game, sf::RenderWindow& window);
	};

	struct TableRecordState
	{
		sf::Text tableRecordsText;
		std::vector <sf::Text> playerRecordText;

		void DrawTableRecordState(Game& game, sf::RenderWindow& window);
	};
	struct QuestionNameState
	{
		sf::Text questionEnterPlayerNameText;
		sf::RectangleShape questionEnterPlayerNameBox;
		std::vector <Button> questionEnterNameButtons;

		void DrawQuestionNameState(Game& game, sf::RenderWindow& window);
	};

	struct DifficultyState
	{
		sf::Text changeDifficultyLevelText;
		std::vector <Button> difficultyLevelButtons;

		void DrawDifficultyState(Game& game, sf::RenderWindow& window);
	};

	struct PauseState
	{
		void DrawPauseState(Game& game, sf::RenderWindow& window);
	};

	struct GameOver
	{
		void DrawGameOverState(Game& game, sf::RenderWindow& window);
	};

	struct EnterNameState
	{
		sf::RectangleShape enterNameBox;
		sf::Text userEnteredText;
		std::string enteredText;
		sf::String playerName = "XYZ";

		void DrawEnterNameState(Game& game, sf::RenderWindow& window);
	};

	struct GameUIData
	{
		sf::Font gameFont;
		sf::Text logoText;
		sf::Text pauseText;
		sf::Text gameOverText;

		std::vector <Button> buttons;
		std::vector <Button> pauseButtons;
		std::vector <Button> gameOverButtons;
		int activeButtonIndex = 0;

		sf::Texture mainMenuBackgroundTexture;
		sf::Texture snakeHeadTexture;
		sf::Texture snakeBodyTexture;
		sf::Texture snakeBodyRotationTexture;
		sf::Texture snakeTailEndTexture;

		sf::Texture appleTexture;
		sf::Texture totalNumApplesTexture;

		sf::Texture wallTexture;

		PlayState playState;
		MainMenuState mainMenu;
		SettingsState settings;
		TableRecordState tableRecord;
		QuestionNameState questionName;
		DifficultyState difficultyState;
		PauseState pause;
		GameOver gameOver;
		EnterNameState enterName;

		sf::Sprite mainMenuBackgroundSprite;
	};

	//int CurrentActiveButton(const std::vector <Button> button);
	void SetTextCenter(sf::Text& text);
	void InitText(sf::Text& text, sf::Font& font, int CharacterSize, float PositionX, float PositionY, const sf::String& stringText);
}