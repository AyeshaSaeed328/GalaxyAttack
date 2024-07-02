#include "Enemy.hpp"

class BlueRing : public Enemy //blue ring is the child class of the parent class enemy 
{
    SDL_Rect src, mover;
    bool isClicked = false;

public:
    BlueRing(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov);

    void draw(SDL_Renderer *, SDL_Texture *assets);
    int LifeDeduct();
    void dropEnemies();
    void animateEnemy();
    bool getIsClicked();
    void setIsClicked();
    bool outOfScreen();
    SDL_Rect getMov();
    SDL_Rect getSrc();
};