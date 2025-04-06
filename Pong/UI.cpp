#include "UI.h"

void UI::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTs::Failled to load Roboto-Regular.ttf!" << '\n';
    }

}

void UI::initText()
{
    //uiText
    this->uiText.setFont(this->font);
    this->uiText.setStyle(sf::Text::Bold);
    this->uiText.setCharacterSize(60);
    

    //mainMenuText
    this->mainMenuText.setFont(this->font);
    this->mainMenuText.setCharacterSize(35);

    //endGameText
    this->endGameText.setFont(this->font);
    this->endGameText.setStyle(sf::Text::Bold);
    this->endGameText.setCharacterSize(50);
}

UI::UI()
{
    this->initFonts();
    this->initText();
}

UI::~UI()
{

}

void UI::setGameStates(float endGAme, float gameStart)
{
    this->endGame = endGAme;
    this->gameStart = gameStart;
}

void UI::update(float playerPoints, float enemyPoints, const sf::RenderTarget* target)
{

    std::stringstream ss;

    //Main Menu update

    if (!gameStart)
    {
        this->uiText.setString("Pong");
        this->uiText.setPosition(
            static_cast<float>((target->getSize().x - this->uiText.getGlobalBounds().width) / 2),
            100.f
        );

        this->mainMenuText.setString("- Press Enter to start \n\n- Press Esc to close the game ");
        this->mainMenuText.setPosition(
            static_cast<float>((target->getSize().x - this->mainMenuText.getGlobalBounds().width) / 2.f),
            target->getSize().y / 2.f - this->mainMenuText.getGlobalBounds().height / 2.f  
        );
    }

    //UI Text update


    else if (!endGame && gameStart)
    {

        ss << enemyPoints << "  :  " << playerPoints;

        this->uiText.setString(ss.str());
        this->uiText.setPosition(
            static_cast<float>((target->getSize().x - this->uiText.getGlobalBounds().width) / 2),
            0.f
            );
    }


    //End Game update

    else if (endGame)
    {
        if (playerPoints == 10)
            this->endGameText.setString("You won!");
        else if(enemyPoints == 10)
            this->endGameText.setString("You lost!");

        this->endGameText.setPosition(
            static_cast<float>((target->getSize().x - this->endGameText.getGlobalBounds().width) / 2),
            100.f
        );

        this->mainMenuText.setString("- Press Esc to close the game ");
        this->mainMenuText.setPosition(
            static_cast<float>((target->getSize().x - this->mainMenuText.getGlobalBounds().width) / 2.f),
            target->getSize().y / 2.f - this->mainMenuText.getGlobalBounds().height / 2.f
        );
    }

}

void UI::render(sf::RenderTarget* target)
{

    if (!gameStart)
    {
        target->draw(this->uiText);
        target->draw(this->mainMenuText);
    }
        
    else if (!endGame && gameStart)
    {
        target->draw(this->uiText);
    }

    else if (endGame)
    {
        target->draw(this->endGameText);
        target->draw(this->mainMenuText);
    }

}
