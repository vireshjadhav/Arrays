//MianMenuManager.h
#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/UIElements/Button/Button.h"



namespace UI
{
	using namespace UIElements;

	class MainMenuManager
	{
	private:
		sf::RenderWindow* game_window;
		sf::Texture background_texture;
		sf::Sprite background_sprite;

		Button* play_button;
		Button* quit_button;

		const std::string background_texture_path = "assets/textures/minesweeper_bg.png";
		const std::string play_button_path = "assets/textures/play_button.png";
		const  std::string quit_button_path = "assets/textures/quit_button.png";

		const float button_width = 300.0f;
		const float button_hieght = 100.0f;
		const float play_button_y_position = 600.0f;
		const float quit_button_y_position = 750.0f;
		const float background_alpha = 85.0f;

		void initialize();
		void initializeBackground();
		void initializeButtons();

		void playButtonCallback(MouseButtonType mouse_button_type);
		void quitButtonCallback(MouseButtonType mouse_button_type);
		void registerButtonCallback();

		sf::Vector2f getButtonPosition(float offsetX, float offsetY);

	public:

		MainMenuManager(sf::RenderWindow* window);
		~MainMenuManager();

		void update(Event::EventPollingManager& eventmanager);
		void render();
		void show();

		void checkForButtonClicks(Event::EventPollingManager& eventmanager);
	};
}