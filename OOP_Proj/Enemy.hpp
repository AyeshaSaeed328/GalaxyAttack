#pragma once
#include <SDL.h>
#include <time.h>


class Enemy
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;

public:
    // SDL_Rect getMov();
    Enemy(SDL_Renderer *, SDL_Texture *);
    virtual void draw(SDL_Renderer *, SDL_Texture *,SDL_Rect ,SDL_Rect );
    virtual void dropEnemies();
    virtual void animateEnemy();
    virtual int LifeDeduct()=0; // pure virtual void function.
    virtual SDL_Rect getMov();
    virtual SDL_Rect getSrc();
    virtual bool getIsClicked();
    virtual void setIsClicked();
    virtual bool outOfScreen();
};
