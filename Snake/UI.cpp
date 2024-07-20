#include "UI.h"
#include "Game.h"
#include <algorithm>

namespace Snake
{
	void SetTextCenter(sf::Text& text)
	{
		sf::FloatRect rect = text.getLocalBounds();
		text.setOrigin(rect.left + rect.width / 2.f,
			rect.top + rect.height / 2.f);
	}
	void InitText(sf::Text& text, sf::Font& font, int CharacterSize, float PositionX, float PositionY, const sf::String& stringText)
	{
		text.setFont(font);
		text.setCharacterSize(CharacterSize);
		text.setPosition(PositionX, PositionY);
		text.setString(stringText);
		SetTextCenter(text);
	}

	void Button::Init(const std::string& text, sf::Font& font, int characterSize, const sf::Vector2f& position)
	{
		isActive = false;
		buttonText.setFont(font);
		buttonText.setCharacterSize(characterSize);
		buttonText.setString(text);
		buttonText.setPosition(position);
		buttonText.setFillColor(sf::Color::Black);

		SetTextCenter(buttonText);
		this->position = position;
	}
	void Button::Draw(sf::RenderWindow& window)
	{
		window.draw(buttonText);
	}
	void Button::ChangeColor(sf::Color color)
	{
		buttonText.setFillColor(color);
	}
	void Button::SetActive(bool active)
	{
		if (active) {
			ChangeColor(sf::Color::Red);
		}
		else{
			ChangeColor(sf::Color::Black);
		}
	}
	bool Button::IsActive() const
	{
		return isActive;
	}
	void PlayState::DrawPlayState(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.playState.numAppleUI);
		window.draw(game.gameUIData.playState.numEatenAppleText);
		window.draw(game.gameUIData.playState.totalNumApplesSprite);
		window.draw(game.gameUIData.playState.totalNumApplesText);


		for (size_t row = 0; row < 15; row++) {
			for (size_t col = 0; col < 15; col++)
			{
				window.draw(game.playField[row][col]);
			}
		}

		for (auto& apples : game.apple) {
			if (!apples.isAppleEaten) {
				apples.Draw(window);
			}
		}

		for (auto& walls : game.wall) {
			walls.Draw(window);
		}

		if (START_TO_MOVE > PAUSE_TO_START_MOVE) {
			window.draw(game.gameUIData.playState.timeToStartMove);
		}

		game.player.DrawPlayer(game.player, window);
	}
	void MainMenuState::DrawMainMenu(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.mainMenuBackgroundSprite);
		window.draw(game.gameUIData.logoText);
		for (auto& button : game.gameUIData.buttons) {
			button.Draw(window);
		}
	}
	void SettingsState::DrawSettingsState(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.mainMenuBackgroundSprite);
		window.draw(game.gameUIData.logoText);
		window.draw(game.gameUIData.settings.settingsText);
		window.draw(game.gameUIData.settings.soundOntext);
		window.draw(game.gameUIData.settings.effectsOntext);
		for (auto& button : game.gameUIData.settings.settingsButtons) {
			button.Draw(window);
		}
	}
	void TableRecordState::DrawTableRecordState(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.mainMenuBackgroundSprite);
		window.draw(game.gameUIData.tableRecord.tableRecordsText);
		for (auto& player : game.gameUIData.tableRecord.playerRecordText) {
			player.setFillColor(sf::Color::White);
			window.draw(player);
		}
	}
	void QuestionNameState::DrawQuestionNameState(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.questionName.questionEnterPlayerNameBox);
		window.draw(game.gameUIData.questionName.questionEnterPlayerNameText);
		for (auto& button : game.gameUIData.questionName.questionEnterNameButtons) {
			button.Draw(window);
		}
	}
	void DifficultyState::DrawDifficultyState(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.mainMenuBackgroundSprite);
		window.draw(game.gameUIData.difficultyState.changeDifficultyLevelText);
		for (auto& button : game.gameUIData.difficultyState.difficultyLevelButtons) {
			button.Draw(window);
		}
	}
	void PauseState::DrawPauseState(Game& game, sf::RenderWindow& window)
	{
		for (auto& button : game.gameUIData.pauseButtons) {
			button.Draw(window);
		}

		window.draw(game.gameUIData.pauseText);
	}
	void GameOver::DrawGameOverState(Game& game, sf::RenderWindow& window)
	{
		for (size_t row = 0; row < 15; row++) {
			for (size_t col = 0; col < 15; col++)
			{
				window.draw(game.playField[row][col]);
			}
		}
		for (auto& apples : game.apple) {
			if (!apples.isAppleEaten) {
				apples.Draw(window);
			}
		}
		for (auto& walls : game.wall) {
			walls.Draw(window);
		}
		game.player.DrawPlayer(game.player, window);

		for (auto& button : game.gameUIData.gameOverButtons) {
			button.Draw(window);
		}

		window.draw(game.gameUIData.tableRecord.tableRecordsText);
		for (auto& player : game.gameUIData.tableRecord.playerRecordText) {
			player.setFillColor(sf::Color::White);
			window.draw(player);
		}
		window.draw(game.gameUIData.gameOverText);
	}
	void EnterNameState::DrawEnterNameState(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.gameUIData.enterName.enterNameBox);
		window.draw(game.gameUIData.enterName.userEnteredText);
	}
}

