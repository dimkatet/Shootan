#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Window.hpp>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Game/EnemyFactory.h"
#include "Game/EntityDestroyer.h"
#include "Components/GameObject.h"
#include "Components/GameStates.h"
#include "Components/Collision.h"
#include "Player/Player.h"
#include "Creatures/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Weapons/AssaultRifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/Gun.h"
#include "Weapons/SniperRifle.h"
#include "Perks/Perk.h"
#include "Perks/Medicine.h"
#include "Perks/Fire.h"
#include "Perks/Frost.h"
#include "Perks/FindWeapon.h"
#include "Perks/UpSpeed.h"
#include "GUI/Menu.h"
#include "GUI/PauseMenu.h"
#include "GUI/HealthBar.h"
#include "GUI/AmmoBar.h"
#include "GUI/LvlBar.h"
#include "GUI/PerkMenu.h"
#include "GUI/GameOverMenu.h"
#include "Utils/FPSCounter.h"
#include "Utils/ResourceManager.h"
#include "Utils/AudioSettings.h"
#include "Utils/VideoSettings.h"

//
#include "Obstacles/Obstacles.h"
#include "Obstacles/DeathZone.h"
#include "Obstacles/Wall.h"

class GameState
{
public:
    GameState() {};
    virtual ~GameState() {};
    virtual GameStates   update()=0;
    virtual void         draw()=0;
    virtual void         handleEvents(sf::Event) {};
protected:

private:
};

#endif // GAMESTATE_H
