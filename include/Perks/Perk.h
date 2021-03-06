#ifndef PERK_H
#define PERK_H

#include "Components/GameObject.h"
#include "Player/Player.h"
#include "Utils/ResourceManager.h"


class Perk : public GameObject
{
    public:
        Perk(int _xPos, int _yPos);
        virtual ~Perk();
        virtual void pickUp(Player* players = player)=0;
        void update();
        bool checkActive();
        static Player* player;
    protected:
        float activeTime;
        float raz;
        float currentTimeIncrease;
        float currentTimeTurn;
        float timeIncrease1;
        float timeIncrease2;
        float timeTurn;
        int degree;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int iAnimation;
};
extern sf::RenderWindow window;
extern float frameTime;
extern ResourceManager      *resources;

#endif // PERK_H
