#pragma once

#include <iostream>
#include <cmath>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Ball
{
private:
	//variables
	float ballRadius;
	float ballAngle;
	float ballSpeed;

	float maxAngle;

	sf::Vector2f velocity;

	struct bounds{
		bool top;
		bool down;
		bool left;
		bool right;
	};

	//object
	sf::CircleShape ball;

	//private func
	void initBallVariables();
	void initBall();
	
public:

	Ball();
	virtual ~Ball();

	//get functions

	const sf::CircleShape& getShape() const;
	float getSpeed();
	float getAngle();
	float getMaxAngle();
	const sf::Vector2f& getOrigin() const;
	const sf::Vector2f& getPosition() const;

	//set/reset functions
	void setPosition(float x, float y);
	void setSpeed(float x);
	void setAngle(float x);
	void resetSpeed();
	void resetBall();

	//change functions
	void changeBallDirection();

	//update functions
	void updateMovement(const sf::RenderTarget* target);
	bounds updateGlobalCollision(const sf::RenderTarget* target); // Tis should be a get function
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

