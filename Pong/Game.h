#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <cmath>

#include "Player.h"
#include "Ball.h"
#include "Enemy.h"
#include "UI.h"

/*
    Class that acts as the game engine.
    Wrapped Class.
*/

class UI;

class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Vector2f paddleSize;

    float enemySpeed;
    bool possesion;

    //Game Objects
    Player player;
    Ball ball;
    Enemy enemy;
    UI gui;
    
    //Game Logic
    
    //game states
    bool endGame;
    bool gameStart;
    //game points
    int playerPoints;
    int enemyPoints;

    // Private functiones
    void initVariables();
    void initWindow();

public:
    // Constructor / Destructor
    Game();
    virtual ~Game();

    // Accesors
    const bool isRunning() const;

    // Functions
    void updateFonts();
    void updateGui();
    void pollEvents();
    void updateGameState();
    void updateEnemyAI();
    void updatePaddleCollision();
    void updateWinCollision();
    void update();

    void render();
};
