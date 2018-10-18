#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class Shotgun: public Weapon
{
    public:
        Shotgun(sf::Sprite* _player);
        virtual ~Shotgun();
        bool addProjectile();
        int waveNamber=0;
};

#endif //SHOTGUN