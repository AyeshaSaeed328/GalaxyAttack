#pragma once
#include<SDL.h>
#include "SpaceX.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>


class health_and_score{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    int totalHealth;

    public:
    void health_status(int x);
    void update(SDL_Renderer *, SDL_Texture *, int x);

    health_and_score(int);
    void updateHealth(int);
    int getHealth();
};