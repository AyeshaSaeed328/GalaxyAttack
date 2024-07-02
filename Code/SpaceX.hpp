#include <SDL.h>
#include "Enemy.hpp"
#include "Obstacle.hpp"

#include "RedAsteroid.hpp"

#include "BlueAsteroid.hpp"

#include "Collectible.hpp"
#include "Spaceship.hpp"
#include "Health.hpp"
#include "Diamond.hpp"
#include "Score.hpp"
#include "HealthPoints.hpp"
#include <list>
#include <SDL_ttf.h>
using namespace std;
#include <string>





class SpaceX
{
    list<Obstacle *> Obstacles;
    list<Enemy *> Enemies;
    list<Collectible *> Collectibles;
    Spaceship* spaceship_in_game;
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    Score totalScore;
    HealthPoints totalHealth;

public:
    SpaceX(SDL_Renderer *, SDL_Texture *, Score &, HealthPoints &);
    void drawObjects();
    void displayHealth();
    void displayScore();
    void createObject();
    void createSpaceship(int spaceship);
    void drawSpaceship();
    bool collisionDetection(SDL_Rect *,SDL_Rect *);
    Spaceship* getSpaceship();
    void checkMouseClick(int, int, int&);
    void deleteObjects();
    // void dropObjects();
    // void fire();
    ~SpaceX();
};