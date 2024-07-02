#pragma once
#include <SDL.h>

class HealthPoints
{
    
    int totalHealth;
    int totalGems = 0;

public:
    HealthPoints(int);
    void updateHealth(int);
    int getHealth();
    int getGems();
    void updateGems();
    
};