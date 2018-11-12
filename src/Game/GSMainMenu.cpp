#include "Game/GSMainMenu.h"

GSMainMenu::GSMainMenu(VideoSettings *_videoSettings, GameStates *_gameState)
{
    videoSettings = _videoSettings;
    gameState = _gameState;
    isSettings = false;
    loadresources();
    mainMenu = new MainMenu(gameState, &isSettings);
    background.setTexture(resources->getTexture("mainBackground"));
    background.setScale((float)videoSettings->width/background.getTexture()->getSize().x,
                        (float)videoSettings->height/background.getTexture()->getSize().y);
}

GSMainMenu::~GSMainMenu()
{
    //dtor
}

void GSMainMenu::handleEvents(sf::Event event)
{
    if(!isSettings)
        mainMenu->handleEvents(event);
    else
        settingsMenu->handleEvents(event);
}

void GSMainMenu::update()
{
    if(!isSettings && mainMenu == NULL)
    {
        mainMenu = new MainMenu(gameState, &isSettings);
        delete(settingsMenu);
    }
    else if (isSettings && settingsMenu == NULL)
    {
        settingsMenu = new SettingsMenu(videoSettings, &isSettings);
        delete(mainMenu);
    }  
}

void GSMainMenu::loadresources()
{
    resources->addTexture("mainBackground", "./data/GUI/MainMenu/mainBackground.png");
}

void GSMainMenu::draw()
{
    window.draw(background);
    if(!isSettings)
        window.draw(*mainMenu);
    else window.draw(*settingsMenu);
}
