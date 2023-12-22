#pragma once
class Button
{
private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape shape;
public:
	Button(sf::Vector2f size);
	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(int size);
	void setPosition(sf::Vector2f position);
	void setString(std::string str);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPos();
};