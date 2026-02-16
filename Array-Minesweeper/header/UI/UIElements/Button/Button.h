//Button.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"


namespace UIElements
{
	enum class MouseButtonType
	{
		LEFT_MOUSE_BUTTON,
		RIGHT_MOUSE_BUTTON
	};

	class Button
	{
	private:

		// Callback function with a parameter of MouseButtonType
		using CallbackFunction = std::function<void(MouseButtonType)>;
		CallbackFunction callback_function = nullptr;

		sf::Texture buttonTexture;
		sf::Sprite buttonSprite;

		void initialize(const std::string& texture_path, const sf::Vector2f& positon, float width, float height);
		bool isMouseOnSprite(Event::EventPollingManager& event_manager, const sf::RenderWindow& window);

	public:
		Button(const std::string& texture_path, const sf::Vector2f& position, float width, float height);

		void setTextureRect(const sf::IntRect& rect);
		void handleButtonInteractions(Event::EventPollingManager& event_manager, const sf::RenderWindow& window);

		void registerCallbackFunction(CallbackFunction button_callback);

		void render(sf::RenderWindow& window)const;
	};
}