#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "GameObject.h"
#include <iostream>

using namespace std;

class Enemy : public GameObject
{
    public:
        Enemy (int _xPos, int _yPos, const sf::Sprite* _sprite);
        virtual ~Enemy();
        virtual void update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    protected:
        sf::Texture texture;
        const sf::Sprite* player;
        float speed;
        float angle;
        float currentAngle;
        float rotationRate;
        float distance;
        void move();
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // ENEMY_H
