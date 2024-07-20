	#include <cassert>
	#include <string>
	#include "Game.h"
	#include "Constants.h"
	#include "Math.h"

	namespace Snake
	{
		void Init(Game& game)
		{
			assert(game.gameUIData.gameFont.loadFromFile(RESOURCES_PATH + "\\Fonts\\Forque.ttf"));
			assert(game.gameUIData.mainMenuBackgroundTexture.loadFromFile(RESOURCES_PATH + "\\mainMenuBackground.png"));
			assert(game.gameUIData.snakeHeadTexture.loadFromFile(RESOURCES_PATH + "\\Snake_head.png"));
			assert(game.gameUIData.snakeBodyTexture.loadFromFile(RESOURCES_PATH + "\\Snake_Body.png"));
			assert(game.gameUIData.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
			assert(game.gameUIData.snakeTailEndTexture.loadFromFile(RESOURCES_PATH + "\\Tail_end.png"));
			assert(game.gameUIData.snakeBodyRotationTexture.loadFromFile(RESOURCES_PATH + "\\Tail_Body_Rotation.png"));
			assert(game.gameUIData.totalNumApplesTexture.loadFromFile(RESOURCES_PATH + "\\TotalNumApples.png"));
			assert(game.gameUIData.wallTexture.loadFromFile(RESOURCES_PATH + "\\Wall.png"));

			assert(game.gameUIData.mainMenu.mainMenuMusic.openFromFile(RESOURCES_PATH + "\\MainMenuMusic.mp3"));
			assert(game.gameUIData.playState.playStateMusic.openFromFile(RESOURCES_PATH + "\\PlayStateMusic.wav"));
			assert(game.gameUIData.playState.coinUpBuffer.loadFromFile(RESOURCES_PATH + "\\CoinUp.wav"));
			assert(game.gameUIData.playState.endGameBuffer.loadFromFile(RESOURCES_PATH + "EndGame.wav"));
			game.gameUIData.playState.endGame.setBuffer(game.gameUIData.playState.endGameBuffer);
			game.gameUIData.playState.endGame.setVolume(3.f);
			game.gameUIData.playState.coinUp.setBuffer(game.gameUIData.playState.coinUpBuffer);
			game.gameUIData.playState.coinUp.setVolume(0.5f);
			game.gameUIData.mainMenu.mainMenuMusic.setVolume(0.5f);
			game.gameUIData.playState.playStateMusic.setVolume(0.4f);

			InitText(game.gameUIData.logoText, game.gameUIData.gameFont, 120, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f - 60.f, "Snake");
			InitText(game.gameUIData.pauseText, game.gameUIData.gameFont, 80, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f - 60.f, "Pause");
			InitText(game.gameUIData.gameOverText, game.gameUIData.gameFont, 120, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f - 60.f, "Game Over");
			game.gameUIData.playState.numEatenAppleText.setFillColor(sf::Color::White);

			game.gameUIData.mainMenuBackgroundSprite.setTexture(game.gameUIData.mainMenuBackgroundTexture);

			game.playersData.resize(NUM_PLAYERS_RECORD);
			for (auto& player : game.playersData) {
				player.name = "XYZ";
				player.record = rand() % 1000;
			}
			std::sort(game.playersData.begin(), game.playersData.end(), [](const PlayersRecordData& a, const PlayersRecordData& b) {
				return a.record > b.record;
				});

			game.playersData.back().name = game.gameUIData.enterName.playerName;
			game.playersData.back().record = game.totalNumApplesEaten;

			game.apple.resize(NUM_APPLES);
			for (auto& apples : game.apple) {
				apples.Init(game);
			}

			game.wall.resize(NUM_WALLS);
			for (auto& wall : game.wall) {
				wall.Init(game);
			}

			SwitchGameDifficulty(game, GameDifficulty::Middle);

			StartMainMenu(game);
		}

		void UpdateGame(Game& game, float deltaTime)
		{
			GameState currentGameState = CurrentGameState(game);
			switch (currentGameState)
			{
			case Snake::GameState::MainMenu:
				UpdateMainMenu(game);
				break;
			case Snake::GameState::RecordTable:
				UpdateRecordTableState(game);
				break;
			case Snake::GameState::Settings:
				UpdateSettingState(game);
				break;
			case Snake::GameState::Play:
				UpdatePlayingState(game, deltaTime);
				break;
			case Snake::GameState::GameOver:
				UpdateGameOverState(game);
				break;
			case Snake::GameState::Exit:
				break;
			case Snake::GameState::Pause:
				UpdatePauseState(game);
				break;
			case Snake::GameState::PopUpQuestionEnterName:
				UpdatePopUpQuestionEnterNameState(game);
				break;
			case Snake::GameState::PopUpEnterName:
				UpdatePopUpEnterNameState(game);
				break;
			}
		}

		void StartMainMenu(Game& game)
		{
			game.gameUIData.buttons.clear();
			Button startGameButton;
			startGameButton.Init("Start game", game.gameUIData.gameFont, 40, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f + 80.f });
			game.gameUIData.buttons.push_back(startGameButton);

			Button difficultyLevelText;
			difficultyLevelText.Init("Difficulty level", game.gameUIData.gameFont, 40, { startGameButton.position.x, startGameButton.position.y + 40.f });
			game.gameUIData.buttons.push_back(difficultyLevelText);

			Button recordTableText;
			recordTableText.Init("Record table", game.gameUIData.gameFont, 40, { difficultyLevelText.position.x, difficultyLevelText.position.y + 40.f });
			game.gameUIData.buttons.push_back(recordTableText);

			Button settingsText;
			settingsText.Init("Settings", game.gameUIData.gameFont, 40, { recordTableText.position.x, recordTableText.position.y + 40.f });
			game.gameUIData.buttons.push_back(settingsText);

			Button exitGameButton;
			exitGameButton.Init("ExitGame", game.gameUIData.gameFont, 40, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f + 240.f });
			game.gameUIData.buttons.push_back(exitGameButton);

			game.gameUIData.activeButtonIndex = 0;
			game.gameUIData.buttons[0].SetActive(true);

			game.gameUIData.playState.playStateMusic.stop();

			if (game.soundOn) {
				game.gameUIData.mainMenu.mainMenuMusic.play();
			}

			SwitchGameState(game, GameState::MainMenu);
		}
		void UpdateMainMenu(Game& game)
		{

		}

		void StartRecordTableState(Game& game)
		{
			game.gameUIData.tableRecord.playerRecordText.resize(NUM_PLAYERS_RECORD);

			InitText(game.gameUIData.tableRecord.tableRecordsText, game.gameUIData.gameFont, 50, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f - 100, "Table record");
			

			sf::Text userName;
			userName.setString(game.gameUIData.enterName.userEnteredText.getString());
			auto it = std::find_if(game.playersData.begin(), game.playersData.end(), [&userName](const PlayersRecordData& data) {return data.name == userName.getString();});

			if (it != game.playersData.end()) {
				for (size_t i = 0; i < NUM_PLAYERS_RECORD; i++)
				{
					if (game.playersData[i].name == game.gameUIData.enterName.userEnteredText.getString()) {
						game.playersData[i].record = game.totalNumApplesEaten;
					}
				}
			}
			else {
				game.playersData.back().record = game.totalNumApplesEaten;
			}

			std::sort(game.playersData.begin(), game.playersData.end(), [](PlayersRecordData playerData1, PlayersRecordData playerData2) {return playerData1.record > playerData2.record;});

			for (size_t i = 0; i < NUM_PLAYERS_RECORD; i++)
			{
				InitText(game.gameUIData.tableRecord.playerRecordText[i], game.gameUIData.gameFont, 40, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f + i * 40, game.playersData[i].name + "   " + std::to_string(game.playersData[i].record));
			}
			
			SwitchGameState(game, GameState::RecordTable);
		}
		void UpdateRecordTableState(Game& game)
		{
			
		}

		void StartDifficultyLevelState(Game& game)
		{
			InitText(game.gameUIData.difficultyState.changeDifficultyLevelText, game.gameUIData.gameFont, 60, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f - 50.f, "Select difficulty level");
			SetTextCenter(game.gameUIData.difficultyState.changeDifficultyLevelText);

			game.gameUIData.difficultyState.difficultyLevelButtons.clear();

			Button easyLevel;
			easyLevel.Init("Easy", game.gameUIData.gameFont, 40, { game.gameUIData.difficultyState.changeDifficultyLevelText.getPosition().x, game.gameUIData.difficultyState.changeDifficultyLevelText.getPosition().y + 60 });
			game.gameUIData.difficultyState.difficultyLevelButtons.push_back(easyLevel);

			Button easierLevel;
			easierLevel.Init("Easier", game.gameUIData.gameFont, 40, { easyLevel.position.x, easyLevel.position.y + 40 });
			game.gameUIData.difficultyState.difficultyLevelButtons.push_back(easierLevel);

			Button mediumLevel;
			mediumLevel.Init("Medium", game.gameUIData.gameFont, 40, { easierLevel.position.x, easierLevel.position.y + 40 });
			game.gameUIData.difficultyState.difficultyLevelButtons.push_back(mediumLevel);

			Button harderLevel;
			harderLevel.Init("Harder", game.gameUIData.gameFont, 40, { mediumLevel.position.x, mediumLevel.position.y + 40 });
			game.gameUIData.difficultyState.difficultyLevelButtons.push_back(harderLevel);

			Button hardLevel;
			hardLevel.Init("Hard", game.gameUIData.gameFont, 40, { harderLevel.position.x, harderLevel.position.y + 40 });
			game.gameUIData.difficultyState.difficultyLevelButtons.push_back(hardLevel);

			game.gameUIData.activeButtonIndex = 0;
			game.gameUIData.difficultyState.difficultyLevelButtons[0].SetActive(true);

			SwitchGameState(game, GameState::DifficultyLevel);
		}
		void UpdateDifficultyLevelState(Game& game)
		{
		}

		void StartPlayState(Game& game)
		{
			if (game.soundOn) {
				game.gameUIData.playState.playStateMusic.play();
			}
			
			
			switch (CurrentGameDifficulty(game))
			{
			case GameDifficulty::Easy:
				game.movePause = 1;
				game.rewardSize = 1;
				break;
			case GameDifficulty::Easier:
				game.movePause = 0.8f;
				game.rewardSize = 2;
				break;
			case GameDifficulty::Middle:
				game.movePause = 0.5f;
				game.rewardSize = 3;
				break;
			case GameDifficulty::Harder:
				game.movePause = 0.3f;
				game.rewardSize = 4;
				break;
			case GameDifficulty::Hard:
				game.movePause = 0.1f;
				game.rewardSize = 5;
				break;
			}
			game.gameUIData.playState.numAppleUI.setTexture(game.gameUIData.appleTexture);
			game.gameUIData.playState.numAppleUI.setScale(0.5f, 0.5f);
			SetSpriteRelativeOrigin(game.gameUIData.playState.numAppleUI, 0.5f, 0.5f);
			game.gameUIData.playState.numAppleUI.setPosition(16, 25);

			game.gameUIData.playState.totalNumApplesSprite.setTexture(game.gameUIData.totalNumApplesTexture);
			game.gameUIData.playState.totalNumApplesSprite.setScale(0.09f, 0.09f);
			SetSpriteRelativeOrigin(game.gameUIData.playState.totalNumApplesSprite, 0.5f, 0.5f);
			game.gameUIData.playState.totalNumApplesSprite.setPosition(game.gameUIData.playState.numAppleUI.getPosition().x + 60.f, game.gameUIData.playState.numAppleUI.getPosition().y + 2);

			//Init playfield grid
			for (size_t row = 0; row < 15; row++)
			{
				for (size_t col = 0; col < 15; col++)
				{
					game.playField[row][col].setSize(sf::Vector2f(32, 32));
					game.playField[row][col].setPosition(32 * (float)col, 32 * (float)row);
					game.playField[row][col].setPosition(game.playField[row][col].getPosition().x, game.playField[row][col].getPosition().y + 50);
					if ((row + col) % 2 == 0) {
						game.playField[row][col].setFillColor(sf::Color(124, 252, 0));
					}
					else {
						game.playField[row][col].setFillColor(sf::Color(50, 205, 50));
					}
				}
			}

			game.player.InitPlayer(game.player, game);

			for (auto& apples : game.apple) {
				apples.isAppleEaten = false;
				apples.SetPosition(GetRandomPosition(game));
			}

			for (auto& walls : game.wall) {
				walls.SetPosition(GetRandomPosition(game));
				if (DoShapeCollide(walls.GetWallCollider(walls), game.player.GetPlayerCollider(game.player))) {
					walls.SetPosition(GetRandomPosition(game));
				}
			}

			game.numApplesEaten = 0;

			game.gameUIData.mainMenu.mainMenuMusic.stop();

			START_TO_MOVE = 3;
			InitText(game.gameUIData.playState.timeToStartMove, game.gameUIData.gameFont, 40, SCREEN_WIDTH / 2.f + 45, SCREEN_HEIGHT / 2.f, "Start of movement" + std::to_string(START_TO_MOVE));
			SetTextCenter(game.gameUIData.playState.timeToStartMove);

			SwitchGameState(game, GameState::Play);
		}
		void UpdatePlayingState(Game& game, float deltaTime)
		{
			InitText(game.gameUIData.playState.numEatenAppleText, game.gameUIData.gameFont, 25, 40, 27, "- " + std::to_string(game.numApplesEaten));
			InitText(game.gameUIData.playState.totalNumApplesText, game.gameUIData.gameFont, 25, game.gameUIData.playState.numEatenAppleText.getPosition().x + 60, game.gameUIData.playState.numEatenAppleText.getPosition().y, "- " + std::to_string(game.totalNumApplesEaten));

			if (START_TO_MOVE >= PAUSE_TO_START_MOVE) {
				START_TO_MOVE -= deltaTime;
				game.gameUIData.playState.timeToStartMove.setString("Start of movement " + std::to_string((int)START_TO_MOVE));
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && game.player.direction != PlayerDirection::Left) {
					game.player.SetPlayerDirection(game.player, PlayerDirection::Right);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && game.player.direction != PlayerDirection::Down) {
					game.player.SetPlayerDirection(game.player, PlayerDirection::Up);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && game.player.direction != PlayerDirection::Right) {
					game.player.SetPlayerDirection(game.player, PlayerDirection::Left);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && game.player.direction != PlayerDirection::Up) {
					game.player.SetPlayerDirection(game.player, PlayerDirection::Down);
				}

				game.player.UpdatePlayer(game.player, deltaTime, game);


				if (!DoShapeCollide(game.player.GetPlayerCollider(game.player), GetWindowCollide())) {
					StartGameOverState(game);
				}

				for (auto& wall : game.wall) {
					if (DoShapeCollide(game.player.GetPlayerCollider(game.player), wall.GetWallCollider(wall))) {
						if (game.effectsOn) {
							game.gameUIData.playState.endGame.play();
						}
						StartGameOverState(game);
					}
				}

				for (auto& apple : game.apple) {
					if (DoShapeCollide(game.player.GetPlayerCollider(game.player), apple.GetAppleCollider(apple))) {
						if (game.effectsOn) {
							game.gameUIData.playState.coinUp.play();
						}
						apple.isAppleEaten = true;
						game.numApplesEaten += game.rewardSize;
						game.totalNumApplesEaten += game.rewardSize;
						game.player.IncreaseTailLenght(game.player, game, apple.position);
					}
				}
				for (auto& apples : game.apple) {
					if (apples.isAppleEaten == true) {
						apples.SetPosition(GetRandomPosition(game));
						for (auto& apple : game.apple) {
							for (auto& segment : game.player.tail) {
								if (DoShapeCollide(apples.GetAppleCollider(apples), segment.GetTailCollider(segment))) {
									apples.isAppleEaten = true;
								}
								else {
									apples.isAppleEaten = false;
								}
							}
							for (auto& wall : game.wall) {
								if (DoShapeCollide(apple.GetAppleCollider(apple), wall.GetWallCollider(wall))) {
									apples.isAppleEaten = true;
								}
								else {
									apples.isAppleEaten = false;
								}
							}
						}

					}
				}
				for (auto& segment : game.player.tail) {
					if (DoShapeCollide(segment.GetTailCollider(segment), game.player.GetPlayerCollider(game.player))) {
						if (game.effectsOn) {
							game.gameUIData.playState.endGame.play();
						}
						StartGameOverState(game);
					}
				}
			}
		}

		void StartGameOverState(Game& game)
		{
			game.gameUIData.gameOverButtons.clear();
			Button restartGame;
			restartGame.Init("Restart", game.gameUIData.gameFont, 40, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f + 250.f });
			game.gameUIData.gameOverButtons.push_back(restartGame);

			Button exitToMenu;
			exitToMenu.Init("Exit to menu", game.gameUIData.gameFont, 40, { restartGame.position.x, restartGame.position.y + 40.f });
			game.gameUIData.gameOverButtons.push_back(exitToMenu);

			//InitText(game.gameUIData.numEatenAppleText, game.gameUIData.gameFont, 40 , exitToMenu.position.x, exitToMenu.position.y + 40.f, "Your score: " + std::to_string(game.numApplesEaten));

			game.gameUIData.tableRecord.playerRecordText.resize(NUM_PLAYERS_RECORD);
			InitText(game.gameUIData.tableRecord.tableRecordsText, game.gameUIData.gameFont, 50, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f + 10, "Table record");
			game.gameUIData.tableRecord.tableRecordsText.setFillColor(sf::Color::Black);

			for (size_t i = 0; i < NUM_PLAYERS_RECORD; i++)
			{
				if (game.playersData[i].name == game.gameUIData.enterName.userEnteredText.getString()) {
					game.playersData[i].record = game.totalNumApplesEaten;
				}
			}

			std::sort(game.playersData.begin(), game.playersData.end(), [](PlayersRecordData playerData1, PlayersRecordData playerData2) {return playerData1.record > playerData2.record;});

			for (size_t i = 0; i < NUM_PLAYERS_RECORD; i++)
			{
				InitText(game.gameUIData.tableRecord.playerRecordText[i], game.gameUIData.gameFont, 40, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f + 50 + i * 40, game.playersData[i].name + "   " + std::to_string(game.playersData[i].record));
				game.gameUIData.tableRecord.playerRecordText[i].setFillColor(sf::Color::Black);
			}

			game.gameUIData.activeButtonIndex = 1;
			game.gameUIData.gameOverButtons[1].SetActive(true);

			SwitchGameState(game, GameState::GameOver);
		}
		void UpdateGameOverState(Game& game)
		{
			if (CheckUserPlayerName(game)) {

			}
			else {
				StartPopUpQuestionEnterNameState(game);
			}
		}

		void StartPauseState(Game& game)
		{
			game.gameUIData.pauseButtons.clear();
			Button continueGame;
			continueGame.Init("Continue", game.gameUIData.gameFont, 40, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f });
			game.gameUIData.pauseButtons.push_back(continueGame);

			Button exitToMenu;
			exitToMenu.Init("Exit to menu", game.gameUIData.gameFont, 40, { continueGame.position.x, continueGame.position.y + 40.f });
			game.gameUIData.pauseButtons.push_back(exitToMenu);

			game.gameUIData.activeButtonIndex = 0;
			game.gameUIData.pauseButtons[0].SetActive(true);

			SwitchGameState(game, GameState::Pause);
		}
		void UpdatePauseState(Game& game)
		{
		
		}

		void StartPopUpQuestionEnterNameState(Game& game)
		{
			game.gameUIData.questionName.questionEnterNameButtons.clear();
			
			Button yesButton;
			yesButton.Init("Yes", game.gameUIData.gameFont, 40, { SCREEN_WIDTH / 2.f,SCREEN_HEIGHT / 2.f });
			game.gameUIData.questionName.questionEnterNameButtons.push_back(yesButton);

			Button noButton;
			noButton.Init("No", game.gameUIData.gameFont, 40, { SCREEN_WIDTH / 2.f,SCREEN_HEIGHT / 2.f + 40 });
			game.gameUIData.questionName.questionEnterNameButtons.push_back(noButton);

			InitText(game.gameUIData.questionName.questionEnterPlayerNameText, game.gameUIData.gameFont, 40, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 40, "Enter player name?");
			SetTextCenter(game.gameUIData.questionName.questionEnterPlayerNameText);

			game.gameUIData.questionName.questionEnterPlayerNameBox.setSize({ 300.f, 150.f });
			game.gameUIData.questionName.questionEnterPlayerNameBox.setFillColor(sf::Color::Green);
			game.gameUIData.questionName.questionEnterPlayerNameBox.setPosition(SCREEN_WIDTH / 2.f - 150.f, SCREEN_HEIGHT / 2.f - 75.f);

			game.gameUIData.activeButtonIndex = 0;
			game.gameUIData.questionName.questionEnterNameButtons[0].SetActive(true);

			SwitchGameState(game, GameState::PopUpQuestionEnterName);
		}
		void UpdatePopUpQuestionEnterNameState(Game& game)
		{
		}

		void StartPopUpEnterNameState(Game& game)
		{
			InitText(game.gameUIData.enterName.userEnteredText, game.gameUIData.gameFont, 40, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, "Enter your name");
			game.gameUIData.enterName.userEnteredText.setFillColor(sf::Color::Red);

			game.gameUIData.enterName.enterNameBox.setSize({ 300.f, 150.f });
			game.gameUIData.enterName.enterNameBox.setFillColor(sf::Color::Green);
			game.gameUIData.enterName.enterNameBox.setPosition(SCREEN_WIDTH / 2.f - 150.f, SCREEN_HEIGHT / 2.f - 75.f);

			SwitchGameState(game, GameState::PopUpEnterName);
		}
		void UpdatePopUpEnterNameState(Game& game)
		{
		}

		void StartSettingState(Game& game)
		{
			game.gameUIData.settings.settingsButtons.clear();
			InitText(game.gameUIData.settings.settingsText, game.gameUIData.gameFont, 50, game.gameUIData.logoText.getPosition().x, game.gameUIData.logoText.getPosition().y + 70.f, "Settings");

			Button soundOn;
			soundOn.Init("Music", game.gameUIData.gameFont, 40, {game.gameUIData.settings.settingsText.getPosition().x, game.gameUIData.settings.settingsText.getPosition().y + 60});
			game.gameUIData.settings.settingsButtons.push_back(soundOn);

			Button effetsOn;
			effetsOn.Init("Sound", game.gameUIData.gameFont, 40, { soundOn.position.x, soundOn.position.y + 40 });
			game.gameUIData.settings.settingsButtons.push_back(effetsOn);

			game.gameUIData.activeButtonIndex = 0;
			game.gameUIData.settings.settingsButtons[game.gameUIData.activeButtonIndex].SetActive(true);

			InitText(game.gameUIData.settings.soundOntext, game.gameUIData.gameFont, 40, soundOn.position.x + 70.f, soundOn.position.y, "On");
			InitText(game.gameUIData.settings.effectsOntext, game.gameUIData.gameFont, 40, effetsOn.position.x + 70.f, effetsOn.position.y, "On");

			SwitchGameState(game, GameState::Settings);
		}
		void UpdateSettingState(Game& game)
		{
			if (game.soundOn) {
				game.gameUIData.settings.soundOntext.setString("On");
			}
			else{
				game.gameUIData.settings.soundOntext.setString("Off");
			}
			if (game.effectsOn) {
				game.gameUIData.settings.effectsOntext.setString("On");
			}
			else{
				game.gameUIData.settings.effectsOntext.setString("Off");
			}
		}

		void UpdateInput(Game& game,sf::Event& event)
		{
		
		}
	
		void DrawGame(Game& game, sf::RenderWindow& window)
		{
			if (CurrentGameState(game) == GameState::MainMenu) {
				game.gameUIData.mainMenu.DrawMainMenu(game, window);
			}
			if (CurrentGameState(game) == GameState::RecordTable) {
				game.gameUIData.tableRecord.DrawTableRecordState(game, window);
			}
			if (CurrentGameState(game) == GameState::DifficultyLevel) {
				game.gameUIData.difficultyState.DrawDifficultyState(game,window);
			}
			if (CurrentGameState(game) == GameState::Settings) {
				game.gameUIData.settings.DrawSettingsState(game, window);
			}
			if (CurrentGameState(game) == GameState::Play || CurrentGameState(game) == GameState::Pause) {
				game.gameUIData.playState.DrawPlayState(game, window);
			}
			if (CurrentGameState(game) == GameState::Pause) {
				game.gameUIData.pause.DrawPauseState(game, window);
			}
			if (CurrentGameState(game) == GameState::GameOver) {
				game.gameUIData.gameOver.DrawGameOverState(game, window);
			}
			if (CurrentGameState(game) == GameState::PopUpQuestionEnterName) {
				game.gameUIData.questionName.DrawQuestionNameState(game, window);
			}
			if (CurrentGameState(game) == GameState::PopUpEnterName) {
				game.gameUIData.enterName.DrawEnterNameState(game, window);
			}
			window.display();
		}

		void SwitchGameState(Game& game, GameState gameState)
		{
			game.gameState.push_back(gameState);
		}
		void SwitchGameDifficulty(Game& game, GameDifficulty gameDifficulty)
		{
			game.gameDifficulty.push_back(gameDifficulty);
		}
		GameState CurrentGameState(Game& game)
		{
			return game.gameState.back();
		}
		GameDifficulty CurrentGameDifficulty(Game& game)
		{
			return game.gameDifficulty.back();
		}

		bool CheckUserPlayerName(Game& game)
		{
			for (size_t i = 0; i < NUM_PLAYERS_RECORD; i++)
			{
				if (game.playersData[i].name == game.gameUIData.enterName.userEnteredText.getString()) {
					return true;
				}
			}
			return false;
		}
	}

