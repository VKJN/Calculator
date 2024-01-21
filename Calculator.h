#pragma once
#include "Button.h"
#include <iostream>

class Calculator {
private:
	sf::RenderWindow window;
	std::vector<Button> keyboard;
	std::string keyboardSymbols[5][4] = { {"C", "CE", "x^2", "x^y"},
										  {"7", "8", "9", "+"},
										  {"4", "5", "6", "-"},
										  {"1", "2", "3", "*"},
										  {".", "0", "=", "/"} };
	sf::String stringField = "0";
	sf::Text textField;
	sf::Font fontField;

	float firstValue, secondValue;
	std::string operation;
public:
	Calculator();
	void Run();
private:
	void processEvents();
	void update();
	void render();
};