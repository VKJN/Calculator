#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"
#include "Calculator.h"

Calculator::Calculator() :window(WINDOW_SIZE, "Calculator")
{
	if (!fontField.loadFromFile("ariali.ttf")) {
		//error
	}
	this->textField.setCharacterSize(40);
	this->textField.setFillColor(sf::Color::White);

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

						keyboard[i].setFillColor(keyboard[i].getOutlineColor());

						if (keyboard[i].getString() == "." ||
							keyboard[i].getString() >= "0" &&
							keyboard[i].getString() <= "9") {

							if (stringField == "0") {
								stringField = keyboard[i].getString();
							}

							// Если нажата кнопка с точной, то идет проверка на наличие точки в тексте экрана (если нет, то добавляется)
							else if (keyboard[i].getString() == ".") {
								bool flag = true;
								for (int i = 0; i < stringField.getSize(); i++) {
									if (stringField[i] == '.') flag = false;
								}
								if (flag) stringField += keyboard[i].getString();
							}

							// Проверка, не вышел ли текст за рамки экрана (если да, то перестают добавляться цифры)
							else if (textField.getPosition().x > textField.getCharacterSize() * 2) {
								stringField += keyboard[i].getString();
							}
						}

						// Если выбрано С или СЕ
						else if (keyboard[i].getString() == "C") {
								stringField = "0";
							}
						else if (keyboard[i].getString() == "CE") {
							stringField.erase(stringField.getSize() - 1, 1);
							if (stringField.getSize() == 0) stringField = "0";
						}

						// Если выбрана какая-то операция
						else if (keyboard[i].getString() == "+") {
							firstValue = std::stof(stringField.toAnsiString());
							operation = keyboard[i].getString();
							stringField = "0";
						}

						else if (keyboard[i].getString() == "-") {
							firstValue = std::stof(stringField.toAnsiString());
							operation = keyboard[i].getString();
							stringField = "0";
						}

						else if (keyboard[i].getString() == "*") {
							firstValue = std::stof(stringField.toAnsiString());
							operation = keyboard[i].getString();
							stringField = "0";
						}

						else if (keyboard[i].getString() == "/") {
							firstValue = std::stof(stringField.toAnsiString());
							operation = keyboard[i].getString();
							stringField = "0";
						}

						else if (keyboard[i].getString() == "x^y") {
							firstValue = std::stof(stringField.toAnsiString());
							operation = keyboard[i].getString();
							stringField = "0";
						}

						else if (keyboard[i].getString() == "x^2") {
							firstValue = std::stof(stringField.toAnsiString());
							stringField = std::to_string(firstValue * firstValue);
						}

						// Если нажато равно
						else {
							secondValue = std::stof(stringField.toAnsiString());
							if (operation == "+") {
								stringField = std::to_string(firstValue + secondValue);
							}

							else if (operation == "-") {
								stringField = std::to_string(firstValue - secondValue);
							}

							else if (operation == "*") {
								stringField = std::to_string(firstValue * secondValue);
							}

							else if (operation == "/") {
								stringField = std::to_string(firstValue / secondValue);
							}

							else {
								stringField = std::to_string(pow(firstValue, secondValue));
							}
						}
					}
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			for (int i = 0; i < keyboard.size(); i++) {
				keyboard[i].setFillColor(keyboard[i].getColor());
			}
		}
	}
}

void Calculator::update()
{
	this->textField.setString(stringField);
	this->textField.setPosition
	(sf::Vector2f(WINDOW_SIZE.width - textField.getCharacterSize() / 1.8 * stringField.getSize(),
		buttonSize.y / 2 - textField.getCharacterSize() / 2));

}

void Calculator::render()
{
	window.clear(colorOutlineButton);
	for (auto i : keyboard) {
		i.draw(window);
	}
	this->textField.setFont(fontField);
	window.draw(textField);
	window.display();
}