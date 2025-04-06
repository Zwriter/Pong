#include "Enemy.h"

void Enemy::initVariables()
{
    this->shapeSize = sf::Vector2f(25, 100);
    this->shapePoz = sf::Vector2f(25, 300);
    this->enemySpeed = 5.f;
}

void Enemy::initShape()
{
    this->shape.setPosition(10.f, 10.f);
    this->shape.setSize(shapeSize - sf::Vector2f(3, 3));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOrigin(shapeSize / 2.f);
}

Enemy::Enemy()
{
    this->initVariables();
    this->initShape();
    this->shape.setPosition(shapePoz);
}

Enemy::~Enemy()
{

}

const sf::RectangleShape& Enemy::getShape() const
{
    return this->shape;
}

const sf::Vector2f& Enemy::getPosition() const
{
    return this->shape.getPosition();
}

void Enemy::move(float x, float y)
{
    this->shape.move(x, y);
}

void Enemy::resetPossition()
{
    this->shape.setPosition(shapePoz);
}

bool Enemy::checkCollision(const sf::RenderTarget* target)
{
    sf::FloatRect shapeBounds = this->shape.getGlobalBounds();

        if (shapeBounds.top <= 0.f)			// Top bound
        {
            return true;
        }
        if (shapeBounds.top + shapeBounds.height > target->getSize().y)		// Bottom bound
        {
            return true;
        }
    return false;
}

void Enemy::update(const sf::RenderTarget* target)
{
    this->checkCollision(target);
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}
