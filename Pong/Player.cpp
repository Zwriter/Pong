#include "Player.h"

#include <iostream>

void Player::initVariables()
{
    this->paddleSize = sf::Vector2f(25, 100);
    this->movementSpeed = 5.f;
    this->paddlePoz = sf::Vector2f(775, 300);
}

void Player::initShape()
{
    this->rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    this->rightPaddle.setFillColor(sf::Color::White);
    this->rightPaddle.setOrigin(paddleSize / 2.f);
}

Player::Player()
{
    this->initVariables();
    this->initShape();
    this->rightPaddle.setPosition(paddlePoz);
}

Player::~Player()
{

}

const sf::RectangleShape& Player::getShape() const
{
    return this->rightPaddle;
}

const sf::FloatRect& Player::getGlobalBounds() const
{
    return this->rightPaddle.getGlobalBounds();
}

const sf::Vector2f& Player::getPosition() const
{
    return this->rightPaddle.getPosition();
}

const float Player::getSpeed() const
{
    return this->movementSpeed;
}

void Player::resetPossition()
{
    this->rightPaddle.setPosition(paddlePoz);
}

void Player::updateInput(const sf::RenderTarget* target)
{
    //keyboard input
    //up(W)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f)
    {
        this->rightPaddle.move(0.f, -this->movementSpeed);
    }
    //down(S)
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->rightPaddle.getPosition().y + paddleSize.y / 2 < target->getSize().y - 5.f)
    {
        this->rightPaddle.move(0.f, this->movementSpeed);
    }
}

void Player::update(const sf::RenderTarget* target)
{
    //player movement with restriction

    this->updateInput(target);

}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->rightPaddle);
}
