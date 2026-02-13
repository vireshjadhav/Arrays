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