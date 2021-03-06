#include "Components/Cooldown.h"

Cooldown::Cooldown(float _weaponCooldown) :
    weaponCooldown(_weaponCooldown),
    currentCooldown(0.f)
{

}

float Cooldown::getCooldown()
{
    return weaponCooldown;
}

void Cooldown::setCooldown(float _weaponCooldown)
{
    weaponCooldown = _weaponCooldown;
}
float Cooldown::getCurrentCooldown()
{
    return currentCooldown;
}

void Cooldown::reduceCooldown()
{
    if(currentCooldown < frameTime)
        currentCooldown = 0.f;
    else
        currentCooldown -= frameTime;
}
