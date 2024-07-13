#include "UI.h"
#include "Game.h"
#include <algorithm>

namespace Snake
{
	void SetTextCenter(sf::Text& text)
	{
		sf::FloatRect rect = text.getLocalBounds();
		text.setOrigin(rect.left + rect.width / 2.f,
			rect.top + rect.height / 2.f);
	}
	void InitText(sf::Text& text, sf::Font& font, int CharacterSize, float PositionX, float PositionY, const sf::String& stringText)
	{
		text.setFont(font);
		text.setCharacterSize(CharacterSize);
		text.setPosition(PositionX, PositionY);
		text.setString(stringText);
		SetTextCenter(text);
	}

	void Button::Init(const std::string& text, sf::Font& font, int characterSize, const sf::Vector2f& position)
	{
		isActive = false;
		buttonText.setFont(font);
		buttonText.setCharacterSize(characterSize);
		buttonText.setString(text);
		buttonText.setPosition(position);
		buttonText.setFillColor(sf::Color::Black);

		SetTextCenter(buttonText);
		this->position = position;
	}
	void Button::Draw(sf::RenderWindow& window)
	{
		window.draw(buttonText);
	}
	void Button::ChangeColor(sf::Color color)
	{
		buttonText.setFillColor(color);
	}
	void Button::SetActive(bool active)
	{
		if (active) {
			ChangeColor(sf::Color::Red);
		}
		else{
			ChangeColor(sf::Color::Black);
		}
	}
	bool Button::IsActive() const
	{
		return isActive;
	}
}

