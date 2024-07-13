#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Constants.h"

int main()
{
    using namespace Snake;

    setlocale(LC_ALL, "Russian");

    int seed = (int)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake!");

    // InitGame
    Game game;
    Init(game);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    bool enterPressed = false;

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !enterPressed) {
                    enterPressed = true;

                    if (CurrentGameState(game) == GameState::MainMenu) {
                        switch (game.gameUIData.activeButtonIndex) {
                        case 0:
                            StartPlayState(game);
                            break;
                        case 1:
                            StartDifficultyLevelState(game);
                            break;
                        case 2:
                            StartRecordTableState(game);
                            break;
                        case 3:
                            StartSettingState(game);
                            break;
                        case 4:
                            game.gameState.push_back(GameState::Exit);
                            window.close();
                            break;
                        }
                    }
                    else if (CurrentGameState(game) == GameState::DifficultyLevel) {
                        switch (game.gameUIData.activeButtonIndex) {
                        case 0:
                            SwitchGameDifficulty(game, GameDifficulty::Easy);
                            StartMainMenu(game);
                            break;
                        case 1:
                            SwitchGameDifficulty(game, GameDifficulty::Easier);
                            StartMainMenu(game);
                            break;
                        case 2:
                            SwitchGameDifficulty(game, GameDifficulty::Middle);
                            StartMainMenu(game);
                            break;
                        case 3:
                            SwitchGameDifficulty(game, GameDifficulty::Harder);
                            StartMainMenu(game);
                            break;
                        case 4:
                            SwitchGameDifficulty(game, GameDifficulty::Hard);
                            StartMainMenu(game);
                            break;
                        }
                    }
                    else if (CurrentGameState(game) == GameState::Settings) {
                        switch (game.gameUIData.activeButtonIndex)
                        {
                        case 0:
                            if (game.soundOn) {
                                game.soundOn = false;
                                game.gameUIData.mainMenuMusic.stop();
                            }
                            else {
                                game.soundOn = true;
                                game.gameUIData.mainMenuMusic.play();
                            }
                            break;
                        case 1:
                            if (game.effectsOn) {
                                game.effectsOn = false;
                            }
                            else {
                                game.effectsOn = true;
                            }
                        }
                    }
                    else if (CurrentGameState(game) == GameState::PopUpQuestionEnterName) {
                        switch (game.gameUIData.activeButtonIndex) {
                        case 0:
                            StartPopUpEnterNameState(game);
                            break;
                        case 1:
                            StartMainMenu(game);
                            break;
                        }
                    }
                    else if (CurrentGameState(game) == GameState::Pause) {
                        switch (game.gameUIData.activeButtonIndex) {
                        case 0:
                            SwitchGameState(game, GameState::Play);
                            break;
                        case 1:
                            StartMainMenu(game);
                            break;
                        }
                    }
                    else if (CurrentGameState(game) == GameState::GameOver) {
                        switch (game.gameUIData.activeButtonIndex) {
                        case 0:
                            StartPlayState(game);
                            break;
                        case 1:
                            StartMainMenu(game);
                            break;
                        }
                    }
                    else if (CurrentGameState(game) == GameState::PopUpEnterName) {
                        game.playersData.back().name = game.gameUIData.userEnteredText.getString();
                        StartGameOverState(game);
                    }
                }

                if (CurrentGameState(game) == GameState::MainMenu) {
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        game.gameUIData.buttons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex - 1 + static_cast<int>(game.gameUIData.buttons.size())) % static_cast<int>(game.gameUIData.buttons.size());
                        game.gameUIData.buttons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::S:
                        game.gameUIData.buttons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex + 1 + static_cast<int>(game.gameUIData.buttons.size())) % static_cast<int>(game.gameUIData.buttons.size());
                        game.gameUIData.buttons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::B:
                        switch (CurrentGameState(game))
                        {
                        case GameState::DifficultyLevel:
                            SwitchGameState(game, GameState::MainMenu);
                            break;
                        case GameState::RecordTable:
                            SwitchGameState(game, GameState::MainMenu);
                            break;
                        case GameState::Settings:
                            SwitchGameState(game, GameState::MainMenu);
                            break;
                        }
                    }
                }
                if (CurrentGameState(game) == GameState::RecordTable) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::B:
                        StartMainMenu(game);
                        break;
                    }
                }
                if (CurrentGameState(game) == GameState::DifficultyLevel) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::W:
                        game.gameUIData.difficultyLevelButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex - 1 + static_cast<int>(game.gameUIData.difficultyLevelButtons.size())) % static_cast<int>(game.gameUIData.difficultyLevelButtons.size());
                        game.gameUIData.difficultyLevelButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::S:
                        game.gameUIData.difficultyLevelButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex + 1 + static_cast<int>(game.gameUIData.difficultyLevelButtons.size())) % static_cast<int>(game.gameUIData.difficultyLevelButtons.size());
                        game.gameUIData.difficultyLevelButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::B:
                        StartMainMenu(game);
                        break;
                    }
                }
                if (CurrentGameState(game) == GameState::Settings) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::W:
                        game.gameUIData.settingsButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex - 1 + static_cast<int>(game.gameUIData.settingsButtons.size())) % static_cast<int>(game.gameUIData.settingsButtons.size());
                        game.gameUIData.settingsButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::S:
                        game.gameUIData.settingsButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex + 1 + static_cast<int>(game.gameUIData.settingsButtons.size())) % static_cast<int>(game.gameUIData.settingsButtons.size());
                        game.gameUIData.settingsButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::B:
                        StartMainMenu(game);
                        break;
                    }
                }
                if (CurrentGameState(game) == GameState::Pause) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::W:
                        game.gameUIData.pauseButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex - 1 + static_cast<int>(game.gameUIData.pauseButtons.size())) % static_cast<int>(game.gameUIData.pauseButtons.size());
                        game.gameUIData.pauseButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::S:
                        game.gameUIData.pauseButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex + 1 + static_cast<int>(game.gameUIData.pauseButtons.size())) % static_cast<int>(game.gameUIData.pauseButtons.size());
                        game.gameUIData.pauseButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    }
                }
                if (CurrentGameState(game) == GameState::Play) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::B:
                        StartPauseState(game);
                    }
                }
                if (CurrentGameState(game) == GameState::GameOver) {
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        game.gameUIData.gameOverButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex - 1 + static_cast<int>(game.gameUIData.gameOverButtons.size())) % static_cast<int>(game.gameUIData.gameOverButtons.size());
                        game.gameUIData.gameOverButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::S:
                        game.gameUIData.gameOverButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex + 1 + static_cast<int>(game.gameUIData.gameOverButtons.size())) % static_cast<int>(game.gameUIData.gameOverButtons.size());
                        game.gameUIData.gameOverButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    }
                }
                if (CurrentGameState(game) == GameState::PopUpQuestionEnterName) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::W:
                        game.gameUIData.questionEnterNameButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex - 1 + static_cast<int>(game.gameUIData.questionEnterNameButtons.size())) % static_cast<int>(game.gameUIData.questionEnterNameButtons.size());
                        game.gameUIData.questionEnterNameButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    case sf::Keyboard::S:
                        game.gameUIData.questionEnterNameButtons[game.gameUIData.activeButtonIndex].SetActive(false);
                        game.gameUIData.activeButtonIndex = (game.gameUIData.activeButtonIndex + 1 + static_cast<int>(game.gameUIData.questionEnterNameButtons.size())) % static_cast<int>(game.gameUIData.questionEnterNameButtons.size());
                        game.gameUIData.questionEnterNameButtons[game.gameUIData.activeButtonIndex].SetActive(true);
                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Enter) {
                    enterPressed = false;
                }
            }

            if (CurrentGameState(game) == GameState::PopUpEnterName) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128 && event.text.unicode != '\b') {
                        game.gameUIData.enteredText += static_cast<char>(event.text.unicode);
                        game.gameUIData.userEnteredText.setString(game.gameUIData.enteredText);
                    }
                    else if (event.text.unicode == '\b') {
                        if (!game.gameUIData.enteredText.empty()) {
                            game.gameUIData.enteredText.pop_back();
                            game.gameUIData.userEnteredText.setString(game.gameUIData.enteredText);
                        }
                    }
                }
                /*else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !enterPressed) {
                        game.playersData.back().name = game.gameUIData.enterText.getString();
                        StartGameOverState(game);
                    }
                }*/
            }
        }

        // UpdateGame
        UpdateGame(game, deltaTime);

        window.clear();
        DrawGame(game, window);
    }

    return 0;
}
