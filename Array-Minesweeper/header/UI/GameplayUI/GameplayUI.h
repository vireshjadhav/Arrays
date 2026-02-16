//GameplayUI.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/UIElements/Button/Button.h"

namespace Gameplay {
	class GameplayManager;
}
namespace UI 
{
	using namespace Gameplay;
	using namespace UIElements;
	using namespace Event;

	class GameplayUI 
	{
	private:
		sf::Font bubbleBobbleFont;
		sf::Font dsDigibFont;
	
		// Text elements
		sf::Text mineText;
		sf::Text timeText;

		// Buttone Elements
		Button* restartButton = nullptr;
		bool restartBUttonClicked = false;

		// Constants
		const std::string restartButtonTexturePath = "assets/textures/restart_button";
		const int fontSize = 110;

		const float mineTextTopOffset = 65.0f;
		const float mineTextLeftOffset = 660.0f;

		const float timeTextTopOffset = 65.0f;
		const float timeTextLeftOffset = 1090.0f;

		const float restartButtonTopOffset = 100.0f;
		const float restartButtonLeftOffset = 920.0f;
		
		const float buttonWidth = 80.0f;
		const float buttonHeight = 80.0f;
		const sf::Color textColor = sf::Color::Red;

		GameplayManager* gameplay_Manager;

		void initialize(GameplayManager* gameplay_manager);
		void initializeText();
		void initializeButton();
		void loadFonts();

		void registerButtonCallback();
		void RestartButtonCallback(MouseButtonType mouse_button_type);

	public:
		GameplayUI(GameplayManager* gameplay_manager);
		~GameplayUI() = default;

		void update(int remaining_mines, int remaining_time, EventPollingManager& eventManager, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

	};
}