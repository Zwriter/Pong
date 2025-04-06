#pragma once

#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class UI
{
private:

	// Private functions
	void initFonts();
	void initText();

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text endGameText;
	sf::Text mainMenuText;

	//
	bool endGame;
	bool gameStart;


public:
	UI();
	virtual ~UI();

	void setGameStates(float endGAme, float gameStart);

	void update(float playerPoints, float enemyPoints, const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

