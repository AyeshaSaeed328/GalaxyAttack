#include "BlueAsteroid.hpp"
// blue astroid
BlueAsteroid::BlueAsteroid(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov) : Obstacle(rend, ast)
{
    // these are the co-ordinates found from the asset image.
    mover = mov;
    src = {686, 1120, 124, 102};
}

void BlueAsteroid::draw(SDL_Renderer *gRenderer, SDL_Texture *assets)
{
    // Body of aestroid drawn using sdl draw function.
    Obstacle::draw(gRenderer,assets,src,mover);
}

SDL_Rect BlueAsteroid::getSrc(){ //returns the coordinates
    return src;
}

void BlueAsteroid::cutAnimation() //animation when bullet is hit
{
   
    src = {1439, 438, 107, 121};
}

bool BlueAsteroid::outOfScreen() //function to check if our object has movedd out of screen or not
{
    if (mover.y>700) // this function is being called to delete objects.
    {
        return true;
    }
    return false;
}
void BlueAsteroid::dropObstacles() //dropping object at a random speed
{
    srand(time(0));
    int randomY;
    randomY = 10 + rand() % 15;
    mover.y += randomY;
}

SDL_Rect BlueAsteroid::getMov() //getting dimension
{
    return mover;
}

bool BlueAsteroid::getIsClicked() // checks if collison has happened or not. 
{
    return isClicked; // getter setter function used here.
}

void BlueAsteroid::setIsClicked()
{
    isClicked = true;
}