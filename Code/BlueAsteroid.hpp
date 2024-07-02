#include "Obstacle.hpp"

class BlueAsteroid : public Obstacle // child class of the parent class obstacle.
{
public:
    BlueAsteroid(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov);
    void draw(SDL_Renderer *, SDL_Texture *assets);
    void cutAnimation(); // All the functions that we have called in our cpp class.
    void dropObstacles();
    bool getIsClicked();
    void setIsClicked();
    bool outOfScreen();
    SDL_Rect getMov();
    SDL_Rect getSrc();
};