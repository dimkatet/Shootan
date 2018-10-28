#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Components/GameObject.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Projectile : public GameObject
{
public:
    enum ProjectileType
    {
        ptSprite,
        ptLine
    };
    Projectile(const sf::Sprite* _sprite, float _damage, int _spread, int _numberTexture, float _speed, bool _person);
    Projectile(const sf::Sprite* _sprite, float _damage, int _spread, int _numberTexture, int _numberShot, float _speed, bool _person);
    virtual ~Projectile();
    void  update();
    float getDamage();
    bool person;
private:
    float damage;
    float speed;
    float angle;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern float                frameTime;
extern vector <sf::Texture> vecTextures;
extern sf::RenderWindow     window;
#endif // PROJECTILE_H
