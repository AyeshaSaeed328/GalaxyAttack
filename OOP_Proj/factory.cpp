//#include "Enemy.hpp"
#include "BlueRing.hpp"
#include "EnemySpaceship.hpp"
#include "Bomb.hpp"
#include <SDL.h>


class Enemie_factory
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    int ran;
    
    public:   
    Enemie_factory()
    {};
    Enemy* getObject()
    {
        int randomNumberx;
        ran = 1 + rand() % 10;
        ran = 100 * ran;
        SDL_Rect objectMov = {ran, 10, 75, 90};
        //for(int i = 0; i < 2; i++)
        //{
            int prob = (rand() % 100) + 1 ;
            randomNumberx = 25 + (rand() % 1400);
            // randomNumbery = (rand() % 100);
            int y = 0;

            if (prob < 33)
            {
                Enemy * u = new BlueRing(gRenderer, assets, objectMov);
                return u;
            }
            else if (prob >= 33 && prob <= 66)
            {
                Enemy* u = new  EnemySpaceship(gRenderer, assets, objectMov);
                return u;
            }
            
            else if (prob >= 67 && prob < 101) 
            {
                Enemy * u = new Bomb(gRenderer, assets, objectMov);
                return u;
            }  
    }
};
