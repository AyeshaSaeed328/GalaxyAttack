#include "Health.hpp"

Health::Health(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov) : Collectible(rend, ast)
{
    // Health's location in asset.png
    mover = mov;
    src = {564, 112, 53, 47};
}

void Health::draw(SDL_Renderer *gRenderer, SDL_Texture *assets)
{
    // Body is drawn using the sdl draw function.
    Collectible::draw(gRenderer,assets,src,mover);

}

bool Health::outOfScreen() //checking if health(heart) is still in screen
{
    if (mover.y>700)
    {
        return true;
    }
    return false;
}

void Health::dropCollectibles() //dropping at a random screen
{
    
    srand(time(0));
    int randomY;
    randomY = 5 + rand() % 15;
    mover.y += randomY;
}

Health::healthIncrease() //total increase in health
{
    return 2;
}
SDL_Rect Health::getSrc() //getting coordinates
{
    return src;
}

SDL_Rect Health::getMov()
{
    return mover;
}

void Health::removeCollectible() //removing when the user collects the health
{
    src = {0, 0, 0, 0};
}

bool Health::getIsClicked()
{
    return isClicked;
}

void Health::setIsClicked()
{
    isClicked = true;
}