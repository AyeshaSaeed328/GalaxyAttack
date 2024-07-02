#include "Diamond.hpp"

Diamond::Diamond(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov) : Collectible(rend, ast)
{
    // Diamond's location in asset.png
    mover = mov;
    src = {553, 256, 67, 57};
}

void Diamond::draw(SDL_Renderer *gRenderer, SDL_Texture *assets)
{
    // Body is drawn using the sdl draw function.
    Collectible::draw(gRenderer,assets,src,mover);
}

SDL_Rect Diamond::getSrc() //getting coordinates
{
    return src;
}

bool Diamond::outOfScreen() //checking if diamond has moved out of screen
{
    if (mover.y>700)
    {
        return true;
    }
    return false;
}

void Diamond::dropCollectibles() //dropping it at a random speed
{

    srand(time(0));
    int randomY;
    randomY = 20 + rand() % 15;
    mover.y += randomY;
}

int Diamond::healthIncrease() 
{
    return 1;
}

SDL_Rect Diamond::getMov() //getting its movement
{
    return mover;
}

void Diamond::removeCollectible() //removing when collected
{
    src = {0, 0, 0, 0};
}

bool Diamond::getIsClicked() // function to check if collison has happened or not.
{
    return isClicked;
}

void Diamond::setIsClicked()
{
    isClicked = true;
}