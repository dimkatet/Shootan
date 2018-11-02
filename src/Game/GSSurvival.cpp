#include "Game/GSSurvival.h"

GSSurvival::GSSurvival(VideoSettings *_videoSettings)
{
    videoSettings = _videoSettings;
    resources = new ResourceManager;
    openMainMenu = false;
    loadResources();
    fieldSize = sf::IntRect(0, 0, 3840, 2160);
    background.setTexture(resources->getTexture("backgroundTile"));
    background.setTextureRect(fieldSize);
    info.setFont(font);
    info.setFillColor(sf::Color::Black);
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    player = new Player;
    //!
    player->setWeapon(new SniperRifle(&player->m_sprite, 1));
    vecEnemies.push_back(new Enemy(500, 500, &player->m_sprite, 100.f));
    vecEnemies.push_back(new Enemy(0, 0, &player->m_sprite, 50.f));
    vecEnemies[0]->setWeapon(new Gun(&(vecEnemies[0])->m_sprite));
    vecEnemies[1]->setWeapon(new Gun(&(vecEnemies[1])->m_sprite));
}

GSSurvival::~GSSurvival()
{
    delete(player);
}

void GSSurvival::update()
{
    if(openMainMenu)
        return;
    player->update();
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        vecEnemies[i]->update();
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
    updateView();
    updateStats();
    checkProjectiles();
    checkEnemies();
    collectTrash();
    updateView();
    draw();
}

void GSSurvival::updateStats()
{
    stringstream ss;
    if(player->getWeapon()->getCurrentReloadTime() > 0.f)
        ss << player->getWeapon()->getCurrentReloadTime() << '/' << player->getWeapon()->getReloadTime();
    else
        ss << player->getWeapon()->getCurrentClipSize() << '/' << player->getWeapon()->getClipSize();
    ss << endl <<"HP: "<< player->getCurrentHealthPoints();
    info.setString(ss.str());
}

void GSSurvival::handleEvents(sf::Event _event)
{
    if(openMainMenu)
            menu->processEvents(_event);
        else
            player->handleEvents(_event);
    if(_event.type == sf::Event::KeyPressed)
        if(_event.key.code == sf::Keyboard::Escape)
            {
            if(!openMainMenu)
                menu = new MainMenu(&openMainMenu, &videoSettings->fullscreen, &videoSettings->vsync);
            else
                openMainMenu = false;
            }
}

void GSSurvival::collectTrash()
{
    for(unsigned int i = 0; i<vecProjectiles.size(); i++)
    {
        if(vecProjectiles[i]->m_sprite.getPosition().x > fieldSize.width + 200
                || vecProjectiles[i]->m_sprite.getPosition().x < -200
                || vecProjectiles[i]->m_sprite.getPosition().y > fieldSize.height + 200
                || vecProjectiles[i]->m_sprite.getPosition().y < -200)
            vecProjectiles.erase(vecProjectiles.begin() + i);
    }
}

void GSSurvival::checkProjectiles()
{
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
    {
        for(unsigned int j = 0; j < vecEnemies.size(); j++)
        {
            if(checkCollision(vecProjectiles[i], vecEnemies[j]))
                if(vecProjectiles[i]->person)
                {
                    vecEnemies[j]->takeDamage(vecProjectiles[i]->getDamage());
                    vecProjectiles.erase(vecProjectiles.begin() + i);
                }
        }
        if(checkCollision(vecProjectiles[i], player))
            if(!(vecProjectiles[i]->person))
            {
                player->takeDamage(vecProjectiles[i]->getDamage());
                vecProjectiles.erase(vecProjectiles.begin() + i);
            }
    }
}

void GSSurvival::checkEnemies()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(vecEnemies[i]->toDelete)
        {
            vecEnemies.erase(vecEnemies.begin() + i);
            cout<<i<<" deleted"<<endl;
        }
    }
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(checkCollision(player, vecEnemies[i]))
        {
            player->takeDamage(vecEnemies[i]->attack());
        }
    }
}

void GSSurvival::updateView()
{
    view.setCenter(player->m_sprite.getPosition().x, player->m_sprite.getPosition().y);
    if(view.getCenter().x < window.getSize().x / 2)
        view.setCenter(window.getSize().x / 2, view.getCenter().y);
    else if(view.getCenter().x > fieldSize.width - (window.getSize().x / 2))
        view.setCenter(fieldSize.width - (window.getSize().x / 2), view.getCenter().y);
    if(view.getCenter().y < window.getSize().y / 2)
        view.setCenter(view.getCenter().x, window.getSize().y / 2);
    else if(view.getCenter().y > fieldSize.height - (window.getSize().y / 2))
        view.setCenter(view.getCenter().x, fieldSize.height - (window.getSize().y / 2));
}

void GSSurvival::loadResources()
{
    resources->addTexture("backgroundTile", "./data/background/tile1.png", true);
    font.loadFromFile("./data/fonts/arial.ttf");
    vecTextures.push_back(sf::Texture());
    vecTextures[0].loadFromFile("./data/projectiles/projectile1.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[1].loadFromFile("./data/enemies/default_enemy.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[2].loadFromFile("./data/enemies/default_monster_nest.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[3].loadFromFile("./data/projectiles/projectile2.png");
}

void GSSurvival::draw()
{
    //*View of the game board
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        window.draw(*vecEnemies[i]);
    window.draw(*player);
    //* UI
    window.setView(window.getDefaultView());
    window.draw(info);
    if(openMainMenu)
        window.draw(*menu);
}