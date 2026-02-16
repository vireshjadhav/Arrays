//MainMenuManager.cpp
#include "../../header/UI/MainMenu/MainMenuManager.h"
#include "../../header/GameLoop/GameLoop.h"

namespace UI
{
	MainMenuManager::MainMenuManager(sf::RenderWindow* window)
	{
		game_window = window;

		initialize();
	}

	MainMenuManager::~MainMenuManager()
	{
		delete play_button;
		delete quit_button;
	}

	void MainMenuManager::initializeBackground()
	{
		if (!background_texture.loadFromFile(background_texture_path))
		{
			std::cerr << "Error loading background texture" << std::endl;
			return;
		}

		background_sprite.setTexture(background_texture);
		background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
	}

	void MainMenuManager::initialize()
	{
		initializeBackground();
		initializeButtons();
	}
	

	void MainMenuManager::initializeButtons()
	{
		play_button = new Button(play_button_path, getButtonPosition(0.0f, play_button_y_position), button_width, button_hieght);
		quit_button = new Button(quit_button_path, getButtonPosition(0.0f, quit_button_y_position), button_width, button_hieght);

		registerButtonCallback();
	}

	sf::Vector2f MainMenuManager::getButtonPosition(float offsetX, float offsetY)
	{
		float x_position = (game_window->getSize().x - button_width) / 2.0f + offsetX;
		float y_position = offsetY;
		return sf::Vector2f(x_position, y_position);
	}

	void MainMenuManager::registerButtonCallback()
	{
		play_button->registerCallbackFunction([this](UIElements::MouseButtonType buttonType)
			{
				playButtonCallback(buttonType);
			}
		);

		quit_button->registerCallbackFunction([this](UIElements::MouseButtonType buttonType)
			{
				quitButtonCallback(buttonType);
			}
		);
	}

	void MainMenuManager::playButtonCallback(UIElements::MouseButtonType mouse_button_type)
	{
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			GameLoop::setGameState(GameState::GAMEPLAY);
		}
	}

	void MainMenuManager::quitButtonCallback(UIElements::MouseButtonType mouse_button_type)
	{
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			GameLoop::setGameState(GameState::EXIT);
		}
	}

	void MainMenuManager::update(EventPollingManager& eventmanager)
	{
		checkForButtonClicks(eventmanager);
	}

	void MainMenuManager::render()
	{
		show();
	}

	void MainMenuManager::show()
	{
		game_window->draw(background_sprite);

		if (play_button) play_button->render(*game_window);
		if (quit_button) quit_button->render(*game_window);
	}

	void MainMenuManager::checkForButtonClicks(EventPollingManager& eventmanager)
	{
		play_button->handleButtonInteractions(eventmanager, *game_window);
		quit_button->handleButtonInteractions(eventmanager, *game_window);
	}
}

