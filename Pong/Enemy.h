#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Enemy
{
private:

	sf::RectangleShape shape;
	sf::Vector2f shapeSize;
	sf::Vector2f shapePoz;
	float enemySpeed;

	void initVariables();
	void initShape();

public:
	Enemy();
	virtual ~Enemy();

	const sf::RectangleShape& getShape() const;
	const sf::Vector2f& getPosition() const;

	void move(float x, float y);
	void resetPossition();
	
	bool checkCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

