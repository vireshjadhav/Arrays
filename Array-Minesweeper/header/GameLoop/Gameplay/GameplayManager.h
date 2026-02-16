//GameplayManager.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include "../../header/UI/GameplayUI/GameplayUI.h"

namespace Gameplay
{
	using namespace Event;
	using namespace Time;
	using namespace UI;

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

		GameplayUI* gameplay_UI;

		GameResult game_result;

		const float background_alpha = 85.0f;

		const float max_level_duration = 150.0f;
		const float game_over_time = 11.0f;
		float remaining_time;

		sf::Texture background_texture;
		sf::Sprite background_sprite;
		std::string background_texture_path = "assets/textures/minesweeper_bg.png";

		void initialize();
		void initializeVariables();
		void initializeBackgroundImage();

		bool hasGameEnded();
		void updateRemainingTime();
		void processTimeOver();

		void handleGameplay(EventPollingManager& enventmangaer, sf::RenderWindow& window);

		void gameWon();
		void gameLost();

	public:
		GameplayManager();
		~GameplayManager() =  default;

		void setGameResult(GameResult gameresult);

		void checkGameWin();

		void processGameResult();

		int getRemainingMinesCount() const;

		void update(EventPollingManager& event_manager, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

		void restartGame();
	};
}
