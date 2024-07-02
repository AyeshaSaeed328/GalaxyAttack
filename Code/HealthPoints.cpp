#include "HealthPoints.hpp"
#include <iostream>

HealthPoints::HealthPoints(int th) : totalHealth(th)
{
    
}

void HealthPoints::updateHealth(int h)
{
    if (h == -3)
    {
        totalHealth = totalHealth -3;
    }
    else if (h == -1)
    {
        totalHealth = totalHealth - 1;
    }
    else
    {
        totalHealth += h;
    }
}

void HealthPoints::updateGems()
{
    totalGems += 1;
}

int HealthPoints::getHealth()
{
    return totalHealth;
}

int HealthPoints::getGems()
{
    return totalGems;
}

