#include "RedAsteroid.hpp"
// red astroid
RedAsteroid::RedAsteroid(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov) : Obstacle(rend, ast)
{
    // Object's location in asset.png
    mover = mov;
    src = {246, 19, 78, 71};
}

void RedAsteroid::draw(SDL_Renderer *gRenderer, SDL_Texture *assets) 
{
    // Body is drawn using sdl draw function.
    Obstacle::draw(gRenderer,assets,src,mover);
}

SDL_Rect RedAsteroid::getSrc() //getting coordinates 
{
    return src;
}

bool RedAsteroid::outOfScreen() //checking if it is still in screen
{
    if (mover.y>700)
    {
        return true;
    }
    return false;
}

void RedAsteroid::cutAnimation() //animation when collision takes places
{
    
    src = {1439, 438, 107, 121};
}

void RedAsteroid::dropObstacles() //dropping it at a random speed
{
    srand(time(0));
    int randomY;
    randomY = 10 + rand() % 15;
    mover.y += randomY;
}

SDL_Rect RedAsteroid::getMov() //movemment checker
{
    return mover;
}

bool RedAsteroid::getIsClicked()
{
    return isClicked;
}

void RedAsteroid::setIsClicked()
{
    isClicked = true;
}