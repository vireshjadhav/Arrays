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
	}

	void GameplayManager::render(sf::RenderWindow& window)
	{
		window.draw(background_sprite);

		board->render(window);
	}
}