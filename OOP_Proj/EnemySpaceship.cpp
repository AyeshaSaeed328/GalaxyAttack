#include "EnemySpaceship.hpp"

EnemySpaceship::EnemySpaceship(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov) : Enemy(rend, ast)
{
    // Enemy Spaceship location in asset.png
    mover = mov;
    src = {406, 152, 107,70};
}

void EnemySpaceship::draw(SDL_Renderer *gRenderer, SDL_Texture *assets)
{
    // Body is drawn using the sdl draw function.
    Enemy::draw(gRenderer,assets,src,mover);
}

SDL_Rect EnemySpaceship::getSrc() //getting cooradinates
{
    return src;
}

bool EnemySpaceship::outOfScreen() //checking if it has moved out of screen
{
    if (mover.y>700)
    {
        return true;
    }
    return false;
}

void EnemySpaceship::dropEnemies() //dropping it at random speed
{
    srand(time(0));
    int randomY;
    randomY = 5 + rand() % 15;
    mover.y += randomY;
}

int EnemySpaceship::LifeDeduct() //life deduction when collided
{
    return -1;
}

SDL_Rect EnemySpaceship::getMov()
{
    return mover;
}

void EnemySpaceship::animateEnemy() //animation on collision
{
    src = {554, 180, 54, 54};
}

bool EnemySpaceship::getIsClicked() // function to check if collison has happened or not. 
{
    return isClicked;
}

void EnemySpaceship::setIsClicked()
{
    isClicked = true;
}