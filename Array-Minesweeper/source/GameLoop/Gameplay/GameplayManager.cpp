//GameplayManager.cpp
#include "../../header/GameLoop/Gameplay/GameplayManager.h"

namespace Gameplay 
{
	GameplayManager::GameplayManager()
	{
		initialize();
	}

	void GameplayManager::initialize()
	{
		initializeBackgroundImage();
		initializeVariables();
	}

	void GameplayManager::initializeVariables()
	{
		board = new Board(this);
		remaining_time = max_level_duration; //Start with full time;
	}

	void GameplayManager::initializeBackgroundImage()
	{
		if (!background_texture.loadFromFile(background_texture_path))
		{
			std::cerr << "failed to load background texture!" << std::endl;
		}

		background_sprite.setTexture(background_texture);
		background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
	}

	void GameplayManager::updateRemainingTime()
	{
		remaining_time -= TimeManager::getDeltaTime();
		processTimeOver();
	}

	void GameplayManager::processTimeOver()
	{
		if (remaining_time <= 0)
		{
			remaining_time = 0;
			game_result = GameResult::LOST;
		}
	}

	void GameplayManager::handleGameplay(EventPollingManager& eventmanager, sf::RenderWindow& window)
	{
		updateRemainingTime(); //Update timer first
		board->update(eventmanager, window);  //Then update board
		checkGameWin(); //Check if player has won
	}

	void GameplayManager::checkGameWin()
	{
		if (board->areAllCellsOpen())
			game_result = GameResult::WON;
	}

	void GameplayManager::processGameResult()
	{
		switch (game_result)
		{
		case GameResult::WON:
			gameWon();
			break;
		case GameResult::LOST:
			gameLost();
			break;
		default:
			break;
		}
	}

	void GameplayManager::gameLost()
	{
		Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
		board->setBoardState(BoardState::COMPLETE);
		board->revealAllMines();
	}

	void GameplayManager::gameWon()
	{
		Sound::SoundManager::PlaySound(Sound::SoundType::GAME_WON);
		board->flagAllMines();
		board->setBoardState(BoardState::COMPLETE);
	}

	void GameplayManager::setGameResult(GameResult gameresult)
	{
		this->game_result = gameresult;
	}

	bool GameplayManager::hasGameEnded()
	{
		return game_result != GameResult::NONE;
	}

	void GameplayManager::update(EventPollingManager& event_manager, sf::RenderWindow& window)
	{
		if (!hasGameEnded())
		{
			handleGameplay(event_manager, window);
		}
		else if (board->getBoardStat() != BoardState::COMPLETE)
		{
			processGameResult();
		}
	}

	void GameplayManager::render(sf::RenderWindow& window)
	{
		window.draw(background_sprite);

		board->render(window);
	}
}