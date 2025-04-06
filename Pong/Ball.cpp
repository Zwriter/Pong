#include "Ball.h"
#include <cmath>

void Ball::initBallVariables()
{
	this->ballRadius = 10.f;
    this->maxAngle = 60.f;
    this->ballAngle = static_cast<float>(rand()%60 + 150);
    this->ballSpeed = 4.f;
    
    if (rand() % 2)
        this->ballAngle += 180.f;

}

void Ball::initBall()
{
    this->ball.setRadius(ballRadius - 3);
    this->ball.setFillColor(sf::Color::White);
    this->ball.setOrigin(ballRadius / 2, ballRadius / 2);
}

Ball::Ball()
{
    this->resetBall();
    this->initBallVariables();
    this->initBall();
}

Ball::~Ball()
{

}

//Get Functions

const sf::CircleShape & Ball::getShape() const
{
    return this->ball;
}

float Ball::getSpeed()
{
    return this->ballSpeed;
}

float Ball::getAngle()
{
    return this->ballAngle;
}

float Ball::getMaxAngle()
{
    return this->maxAngle;
}

const sf::Vector2f& Ball::getOrigin() const
{
    return this->ball.getOrigin();
}

//Set Functions

void Ball::setPosition(float x, float y)
{
    this->ball.setPosition(x,y);
}

void Ball::setSpeed(float x)
{
    this->ballSpeed *= x;
}

void Ball::setAngle(float x)
{
    this->ballAngle = x;
}

void Ball::resetSpeed()
{
    this->ballSpeed = 4.f;
}

void Ball::resetBall()
{
    this->ball.setPosition(400.f, 300.f);
}

void Ball::changeBallDirection()
{
    this->ballSpeed *= -1.f;
}

Ball::bounds Ball::updateGlobalCollision(const sf::RenderTarget* target)
{
    sf::FloatRect ballBounds = this->ball.getGlobalBounds();

    bounds bound = {};

    if (ballBounds.left <= 0.f)		// Left bound
    {
        bound.left = true;
    }
    if (ballBounds.left + ballBounds.width > target->getSize().x)		// Right bound
    {
        bound.right = true;
    }
    if (ballBounds.top <= ballSpeed)			// Top bound
    {
        bound.top = true;
    }
    if (ballBounds.top + ballBounds.height > target->getSize().y - ballSpeed)		// Bottom bound
    {
        bound.down = true;
    }

    return bound;
}

void Ball::updateMovement(const sf::RenderTarget* target)
{
    // Convert ballAngle to radians for velocity calculation

    while (ballAngle < 0) ballAngle += 360;
    while (ballAngle >= 360) ballAngle -= 360;

    double angle = ballAngle * M_PI / 180.0;

    // Set velocity based on current angle
    this->velocity = sf::Vector2f(
        this->ballSpeed * cos(angle),
        this->ballSpeed * sin(angle)
    );

    // Get collision result **once**
    bounds collision = this->updateGlobalCollision(target);

    // Handle vertical (top/bottom) bounces
    if (collision.top) {
        ballAngle = 360.0 - ballAngle;
        ball.setPosition(ball.getPosition().x, ball.getGlobalBounds().height + ballSpeed); // Prevent sticking
    }
    else if (collision.down) {
        ballAngle = 360.0 - ballAngle;
        ball.setPosition(ball.getPosition().x, target->getSize().y - ball.getGlobalBounds().height - ballSpeed * 1.4f);
    }

    // Move ball with the updated velocity
    this->ball.move(this->velocity);
}

void Ball::update(sf::RenderTarget* target)
{

    //this->updateGlobalCollision(target);
    this->updateMovement(target);
    
}

void Ball::render(sf::RenderTarget* target)
{
    target->draw(this->ball);
}

const sf::Vector2f& Ball::getPosition() const
{
    return this->ball.getPosition();
}



