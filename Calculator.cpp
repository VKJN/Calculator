#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"
#include "Calculator.h"

Calculator::Calculator() :window(WINDOW_SIZE, "Calculator")
{
	for (int i = 1; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			Button btn(buttonSize);
			if (j == 3 && i > 1) {
				btn.setFillColor(colorFillButtonOrange);
				btn.setOutlineColor(colorOutlineButtonOrange);
				btn.setOutlineThickness(tricknessSize / 2);
			}
			else {
				btn.setFillColor(colorFillButton);
				btn.setOutlineColor(colorOutlineButton);
				btn.setOutlineThickness(tricknessSize);
			}
			btn.setString(keyboardSymbols[i - 1][j]);
			btn.setPosition(sf::Vector2f(j * (buttonSize.x + tricknessSize), i * (buttonSize.y + tricknessSize)));
			keyboard.push_back(btn);
		}
	}
}

void Calculator::Run()
{
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Calculator::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				for (int i = 0; i < keyboard.size(); i++) {
					sf::Vector2f shapePosition = keyboard[i].getPos();

					if (mousePosition.x >= shapePosition.x &&
						mousePosition.x <= shapePosition.x + buttonSize.x &&
						mousePosition.y >= shapePosition.y &&
						mousePosition.y <= shapePosition.y + buttonSize.y) {
						if (i > 3 && keyboard[i].getPos().x + buttonSize.x == WINDOW_SIZE.width) {
							keyboard[i].setFillColor(sf::Color(230, 160, 30, 255));
						}
						else {
							keyboard[i].setFillColor(sf::Color(80, 80, 80, 255));
						}
					}
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				for (int i = 0; i < keyboard.size(); i++) {
					if (i > 3 && keyboard[i].getPos().x + buttonSize.x == WINDOW_SIZE.width) {
						keyboard[i].setFillColor(colorFillButtonOrange);
					}
					else {
						keyboard[i].setFillColor(colorFillButton);
					}
				}
			}
		}
	}
}

void Calculator::update()
{

}

void Calculator::render()
{
	window.clear(colorOutlineButton);
	for (auto i : keyboard) {
		i.draw(window);
	}
	window.display();
}