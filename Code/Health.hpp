#include "Collectible.hpp"

class Health : public Collectible
{
    SDL_Rect src, mover;
    bool isClicked = false;

public:
    Health(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov);
    void draw(SDL_Renderer *, SDL_Texture *assets);
    int healthIncrease();
    void dropCollectibles();
    void removeCollectible();
    bool getIsClicked();
    void setIsClicked();
    bool outOfScreen();
    SDL_Rect getMov();
    SDL_Rect getSrc();
};