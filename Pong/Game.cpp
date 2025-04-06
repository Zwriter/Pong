#include "Game.h"

// Private funct

void ::Game::initVariables()
{
    this->window = nullptr;
    this->endGame = false;
    this->gameStart = false;
    this->possesion = true;
    this->playerPoints = 0;
    this->enemyPoints = 0;
    this->enemySpeed = player.getSpeed() / 2.f;

    if (ball.getAngle() >= 150.f && ball.getAngle() <= 210)
        this->possesion = false;
}

void ::Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "PONG", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(80); // set frame rate to 80 - 100 for a faster game
}

// Constructor / Destructor

Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}


// Accesors

const bool Game::isRunning() const
{
    return this->window->isOpen();
}

// Functions

void ::Game::pollEvents()
{ // Event Poling

    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            if (this->event.key.code == sf::Keyboard::Enter && !gameStart)
                gameStart = true;
            break;
        }
    }
}

void Game::updateGui()
{

    //send game state to ui class
    this->gui.setGameStates(this->endGame, this->gameStart);

    //update gui 
    this->gui.update(this->playerPoints, this->enemyPoints, this->window);
}

void Game::updateGameState()
{
    if (playerPoints == 10 || enemyPoints == 10)
        this->endGame = true;
}

void Game::updatePaddleCollision()
{
    sf::FloatRect ballBounds = this->ball.getShape().getGlobalBounds();
    sf::FloatRect playerBounds = this->player.getShape().getGlobalBounds();
    sf::FloatRect enemyBounds = this->enemy.getShape().getGlobalBounds();

    const float ballRadius = this->ball.getShape().getRadius();
    sf::Vector2f ballPos = this->ball.getPosition();
    sf::Vector2f playerPos = this->player.getPosition();
    sf::Vector2f enemyPos = this->enemy.getPosition();
    sf::Vector2f paddleSize = this->player.getShape().getSize();

    // RIGHT PADDLE (Player)
    if (ballBounds.intersects(playerBounds))
    {
        //paddle speed boost
        if (this->ball.getSpeed() < 5.0f) {
            this->ball.setSpeed(1.2f);
        }

        float relativeIntersectY = (playerPos.y - ballPos.y);
        float normalizedRelativeIntersectionY = relativeIntersectY / (paddleSize.y / 2.f);

        normalizedRelativeIntersectionY = std::max(-1.f, std::min(1.f, normalizedRelativeIntersectionY));

        float bounceAngle = normalizedRelativeIntersectionY * this->ball.getMaxAngle();

        this->ball.setAngle(180.f + bounceAngle);

        this->ball.setPosition(playerPos.x - ballRadius - paddleSize.x / 2.f - 0.1f, ballPos.y);
    }

    // LEFT PADDLE (Enemy)
    if (ballBounds.intersects(enemyBounds))
    {
        //paddle speed boost
        if (this->ball.getSpeed() < 5.0f) {
            this->ball.setSpeed(1.2f);
        }

        float relativeIntersectY = (enemyPos.y - ballPos.y);
        float normalizedRelativeIntersectionY = relativeIntersectY / (paddleSize.y / 2.f);

        normalizedRelativeIntersectionY = std::max(-1.f, std::min(1.f, normalizedRelativeIntersectionY));

        float bounceAngle = normalizedRelativeIntersectionY * this->ball.getMaxAngle();

        this->ball.setAngle(0.f - bounceAngle);

        this->ball.setPosition(enemyPos.x + ballRadius + paddleSize.x / 2.f + 0.1f, ballPos.y);
    }
}

void Game::updateEnemyAI()
{
    float enemyPoz = this->enemy.getPosition().y;
    float ballPoz = this->ball.getPosition().y;

    if (ballPoz > enemyPoz + 5 && enemyPoz + this->enemy.getShape().getSize().y / 2 < this->window->getSize().y - 15.f)
        this->enemy.move(0, enemySpeed);
    else if (ballPoz < enemyPoz - 5 && enemyPoz - this->enemy.getShape().getSize().y / 2 > 15.f )
        this->enemy.move(0, -enemySpeed);
}


void Game::updateWinCollision() //alternatie possesion (needs to be done) ||| RN The enemy is the only one serving
{

    float angle;

    if (this->ball.updateGlobalCollision(this->window).right || this->ball.updateGlobalCollision(this->window).left)
    {
        if (possesion)
            std::cout << "player has possesion \n";
            
        else
            std::cout << "enemy has possesion \n";
            
        this->possesion = !this->possesion;
    }

    if(possesion)
        angle = static_cast<float>(rand() % 60 + 150);
    else angle = 180.f + static_cast<float>(rand() % 60 + 150);

    if (this->ball.updateGlobalCollision(this->window).left) //left
    {
        this->ball.resetSpeed();
        this->ball.resetBall();
        this->playerPoints++;
        this->ball.setAngle(angle);
        //this->playerPoints = 10;
    }
    if (this->ball.updateGlobalCollision(this->window).right) //right
    {
        this->ball.resetBall();
        this->ball.resetSpeed();
        this->enemyPoints++;
        this->ball.setAngle(angle);
        //this->enemyPoints = 10;
    }
}

void ::Game::update()
{
    //poll events
    this->pollEvents();

    this->updateGui();

    if (!this->endGame && this->gameStart)
    {
        this->player.update(this->window);
        this->enemy.update(this->window);
        this->updateWinCollision();
        this->updatePaddleCollision();
        this->ball.update(this->window);
        this->updateEnemyAI();
        this->updateGameState();
    }

}

void ::Game::render()
{
    /*
        -clear old frame
        -render objects
        -display new frame in window
    */
    this->window->clear();

    // Draw game
    if (!this->endGame && this->gameStart)
    {
        this->player.render(this->window);
        this->enemy.render(this->window);
        this->ball.render(this->window);
    }
    

    //render GUI
    this->gui.render(this->window);

    //display frame
    this->window->display();
}