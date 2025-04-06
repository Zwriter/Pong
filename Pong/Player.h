#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Player
{
private:
	sf::RectangleShape rightPaddle;
	sf::Vector2f paddleSize;
	sf::Vector2f paddlePoz;
	float movementSpeed;

	void initVariables();
	void initShape();

public:
	Player();
	virtual ~Player();

	const sf::RectangleShape& getShape() const;
	const sf::FloatRect& getGlobalBounds() const;
	const sf::Vector2f& getPosition() const;
	const float getSpeed() const;

	void resetPossition();

	void updateInput(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

