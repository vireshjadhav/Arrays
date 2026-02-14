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

	void GameplayManager::setGameResult(GameResult gameresult)
	{
		this->game_result = gameresult;
	}

	bool GameplayManager::hasGameEnded()
	{
		return game_result != GameResult::NONE;
	}

	void GameplayManager::update(Event::EventPollingManager& event_manager, sf::RenderWindow& window)
	{
		if (!hasGameEnded())
			board->update(event_manager, window);
	}

	void GameplayManager::render(sf::RenderWindow& window)
	{
		window.draw(background_sprite);

		board->render(window);
	}
}