#include "Monster.h"

Monster::Monster(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints, float _meleeDamage) :
Enemy(vecTextures[1], _xPos, _yPos, _sprite, _healthPoints, _meleeDamage)
{
    //ctor
}