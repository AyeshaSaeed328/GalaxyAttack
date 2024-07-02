#pragma once
#include <SDL.h>
#include <time.h>

class Collectible
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;

public:
    Collectible(SDL_Renderer *, SDL_Texture *);
    virtual void draw(SDL_Renderer *, SDL_Texture *, SDL_Rect, SDL_Rect);
    virtual int healthIncrease();
    virtual void dropCollectibles(); // All these functions are virtual void functions which we have defined them in parent class.
    virtual void removeCollectible();
    virtual bool getIsClicked();
    virtual void setIsClicked();
    virtual SDL_Rect getMov();
    virtual SDL_Rect getSrc();
    virtual bool outOfScreen();
};
