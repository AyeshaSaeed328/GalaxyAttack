#include "Obstacle.hpp"

class RedAsteroid : public Obstacle
{
    SDL_Rect src, mover;
    bool isClicked = false;

public:
    RedAsteroid(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov);
    void draw(SDL_Renderer *, SDL_Texture *assets);
    void cutAnimation();
    void dropObstacles();
    bool getIsClicked();
    void setIsClicked();
    bool outOfScreen();
    SDL_Rect getMov();
    SDL_Rect getSrc();
};