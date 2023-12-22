#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Button.h"

Button::Button(sf::Vector2f size) :shape(size)
{
	if (!font.loadFromFile("ariali.ttf")) {
		//error
	}
	this->text.setCharacterSize(30);
	this->text.setFillColor(sf::Color::White);
}

void Button::setString(std::string str) {
	this->text.setString(str);
}

void Button::setFillColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Button::setOutlineColor(sf::Color color)
{
	shape.setOutlineColor(color);
}

void Button::setOutlineThickness(int size)
{
	shape.setOutlineThickness(size);
}

void Button::setPosition(sf::Vector2f position)
{
	sf::Vector2f posText(position);
	posText.x += (shape.getSize().x) / 2 - (text.getCharacterSize() / 1.5 * text.getString().getSize()) / 2;
	posText.y += (shape.getSize().y) / 2 - (text.getCharacterSize()) / 2;

	shape.setPosition(position);
	text.setPosition(posText);
}

void Button::draw(sf::RenderWindow& window) {
	this->text.setFont(font);
	window.draw(shape);
	window.draw(text);
}

sf::Vector2f Button::getPos()
{
	return sf::Vector2f(shape.getPosition());
}