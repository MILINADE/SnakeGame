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

		//Play state
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

		//Main menu
		sf::Music mainMenuMusic;
		//Settings
		sf::Text settingsText;
		std::vector <Button> settingsButtons;
		sf::Text soundOntext;
		sf::Text effectsOntext;
		//Table record state
		sf::Text tableRecordsText;
		std::vector <sf::Text> playerRecordText;
		//Question name state
		sf::Text questionEnterPlayerNameText;
		sf::RectangleShape questionEnterPlayerNameBox;
		std::vector <Button> questionEnterNameButtons;
		//Enter name state
		sf::RectangleShape enterNameBox;
		sf::Text userEnteredText;
		std::string enteredText;
		sf::String playerName = "XYZ";
		//Difficulty level state
		sf::Text changeDifficultyLevelText;
		std::vector <Button> difficultyLevelButtons;

		sf::Sprite mainMenuBackgroundSprite;
	};

	//int CurrentActiveButton(const std::vector <Button> button);
	void SetTextCenter(sf::Text& text);
	void InitText(sf::Text& text, sf::Font& font, int CharacterSize, float PositionX, float PositionY, const sf::String& stringText);
}