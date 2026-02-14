//GameplayManager.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

namespace Gameplay
{
	enum class GameResult
	{
		NONE,
		WON,
		LOST
	};

	class GameplayManager 
	{
	private:
		Board* board;

		GameResult game_result;

		const float background_alpha = 85.0f;

		sf::Texture background_texture;
		sf::Sprite background_sprite;
		std::string background_texture_path = "assets/textures/minesweeper_bg.png";

		void initialize();
		void initializeVariables();
		void initializeBackgroundImage();

		bool hasGameEnded();

	public:
		GameplayManager();
		~GameplayManager() =  default;

		void setGameResult(GameResult gameresult);

		void update(Event::EventPollingManager& event_manager, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
	};
}
