#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Window.hpp>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Components/GameObject.h"
#include "Player/Player.h"
#include "Creatures/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Weapons/Autorifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/Gun.h"
#include "Weapons/SniperRifle.h"
#include "Components/Collision.h"
#include "Game/VideoSettings.h"
#include "GUI/Menu.h"
#include "GUI/MainMenu.h"
#include "Utils/FPSCounter.h"
#include "Utils/ResourceManager.h"

class GameState
{
public:
    GameState() {};
    virtual ~GameState() {};
    virtual void update()=0;
    virtual void draw()=0;
    virtual void handleEvents(sf::Event _event) {};
protected:

private:
};

#endif // GAMESTATE_H