//Button.cpp
#include "../../header/UI/UIElements/Button/Button.h"

namespace UIElements 
{
	Button::Button(const std::string& texture_path, const sf::Vector2f& position, float width, float height)
	{
		initialize(texture_path,position,width,height);
	}

	void Button::initialize(const std::string& texture_path, const sf::Vector2f& position, float width, float height)
	{
		if (!buttonTexture.loadFromFile(texture_path))
		{
			std::cerr << "Failed to load button texture: " << texture_path << std::endl;
			return;
		}

		buttonSprite.setTexture(buttonTexture);
		buttonSprite.setPosition(position);
		buttonSprite.setScale(width / buttonTexture.getSize().x, height / buttonTexture.getSize().y);
	}

	bool Button::isMouseOnSprite(Event::EventPollingManager& event_manage, const sf::RenderWindow& window)
	{
		// Get the position of the mouse
		sf::Vector2i mouse_position = event_manage.getMousePosition();

		// Check if the mouse's position is present in the bounds of buttonSprite
		return buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
	}

	void Button::handleButtonInteractions(Event::EventPollingManager& event_manager, const sf::RenderWindow& window)
	{
		if (event_manager.pressedLeftMouseButton() && isMouseOnSprite(event_manager, window))
		{
			callback_function(MouseButtonType::LEFT_MOUSE_BUTTON);
		}

		if (event_manager.pressedRightMouseButton() && isMouseOnSprite(event_manager, window))
		{
			callback_function(MouseButtonType::RIGHT_MOUSE_BUTTON);
		}
	}

	void Button::registerCallbackFunction(CallbackFunction button_callback)
	{
		callback_function = button_callback;
	}

	void Button::setTextureRect(const sf::IntRect& rect)
	{
		//Set a rectangle on the texture
		buttonSprite.setTextureRect(rect);
	}

	void Button::render(sf::RenderWindow& window) const
	{
		window.draw(buttonSprite);
	}
}