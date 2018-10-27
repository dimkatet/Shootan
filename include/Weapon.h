#ifndef WEAPON_H
#define WEAPON_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include "Projectile.h"
#include "Cooldown.h"
using namespace std;

class Weapon : public Cooldown
{
    public:
        Weapon(sf::Sprite* _player, bool _person=0);
        Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize,float _damage, int _spread, Projectile::ProjectileType _projectileType, bool _person=0);
        virtual ~Weapon();
        virtual void update();
        virtual bool addProjectile();
        float getReloadTime();
        float getCurrentReloadTime();
        int getClipSize();
        int getCurrentClipSize();
        float getDistanceAttack();
        virtual float attack(){};
        void getDamage(){};
        void setDamage(float _damage){};
    protected:
        const sf::Sprite* player;
        float reloadTime;
        float currentReloadTime;
        int clipSize;
        int currentClipSize;
        float damage;
        int spread;
        int skills;
        float projectileSpeed;
        float wDistanceAttack;
        bool person;
        Projectile::ProjectileType projectileType;
    private:
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector <Projectile*> vecProjectiles;
#endif // WEAPON_H
