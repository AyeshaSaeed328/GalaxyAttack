#include "Bomb.hpp"

Bomb::Bomb(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov) : Enemy(rend, ast)
{
    // bomb co-ordinates taken out from asset png.
    mover = mov;
    src = {15, 11, 79, 80};
}

void Bomb::draw(SDL_Renderer *gRenderer, SDL_Texture *assets)
{
    // Body of sdl drawn is using draw function.
    Enemy::draw(gRenderer,assets,src,mover);
}

SDL_Rect Bomb::getSrc(){ //returns the coordinates
    return src;
}

bool Bomb::outOfScreen() //function to check if our object has movedd out of screen or not
{
    if (mover.y>700)
    {
        return true;
    }
    return false;
}

void Bomb::dropEnemies() //dropping object at a random speed
{
    //srand(time(0));
    int randomY;
    randomY = 10 + rand() % 15;
    mover.y += randomY;
}

int Bomb::LifeDeduct() //deduction of life if collided
{
    return -3;
}

SDL_Rect Bomb::getMov()
{
    return mover;
}

void Bomb::animateEnemy() //animation when bullet is hit
{
    src = {554, 180, 54, 54};


}

bool Bomb::getIsClicked() // function to check if collision has happened or not.
{
    return isClicked;
}

void Bomb::setIsClicked()
{
    isClicked = true;
}