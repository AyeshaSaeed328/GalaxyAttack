#include "SpaceX.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include "Score.hpp"
#include "HealthPoints.hpp"
#include "factory.cpp"
using namespace std;


void SpaceX::deleteObjects()
{
    SDL_Rect ObjectMov;
    for (auto E : Enemies)
    {
        ObjectMov = E->getMov();
        if (ObjectMov.y > 700) // if enemy out of screen, destroy it
        {
            delete E;
            Enemies.remove(E);
        }
    }
    for (auto F : Obstacles)
    {
        ObjectMov = F->getMov();
        if (ObjectMov.y > 700) // if obstacle out of screen, destroy it
        {
            delete F;
            Obstacles.remove(F);
        }
    }
    for (auto C : Collectibles)
    {
        ObjectMov = C->getMov();
        if (ObjectMov.y > 700) // if collectible out of screen, destroy it
        {
            delete C;
            Collectibles.remove(C);
        }
    }
}

void SpaceX::checkMouseClick(int x, int y, int &Screen) // fucntion where objects of the game are interacting with the bullets and co.
{
    SDL_Rect getmov;              // variable to store movements and locations of enemies, collectibles & obstacles
    SDL_Rect spaceship_loc;       // variable to store movements and locations of spaceship chosen
    SDL_Rect bullet_loc;          // variable to store movement and location of bullet fired
    bool isclicked;               // boolean variable to confirm collision
    list<Bullets *> bullets_list; // variable to store every bullet fired, for use in locating

    bullets_list = spaceship_in_game->getBullets();
    spaceship_loc = spaceship_in_game->getMov();
    int m = 0;
    for (auto B : bullets_list)
    {
        bullet_loc = B->getLocation(); // get bullet location
        

        for (auto F : Obstacles) // first loop around every obstacle present on screen
        {
            isclicked = F->getIsClicked(); // get status of wether collision has happened or not
            getmov = F->getMov();          

            
            if (!isclicked)
            {
                if (SDL_HasIntersection(&bullet_loc, &getmov))
                {
                    cout << "inside isclicked" << endl;
                    F->setIsClicked();
                    F->cutAnimation();
                    B->removeBullet();
                    totalScore.ScoreUpdate();
                    
                }

                cout << "collide" << endl;
            }
            m++;
        }
        for (auto E : Enemies) // now loop over all enemies
        {
            isclicked = E->getIsClicked();  // get status of collision
            getmov = E->getMov();           // get movement and location of enemy
            if (spaceship_loc.y < getmov.y) // if the enemy goes through the screen unharmed you lose health
            {
                if (!isclicked)
                {
                    E->setIsClicked();                         // status changed to collided
                    totalHealth.updateHealth(E->LifeDeduct()); // reduce health by 1 point
                    if (totalHealth.getHealth() <= 0)          // if health goes to 0, game over
                    {
                        Screen = 7; // game over screen
                    }
                }
            }

            else if (SDL_HasIntersection(&bullet_loc, &getmov))
            {
                E->setIsClicked();
                E->animateEnemy();
                totalScore.ScoreUpdate();
                B->removeBullet();
            }
        }
        for (auto C : Collectibles) // finally, loop over all collectibles present on screen
        {
            string checker = typeid(*C).name();
            // cout <<"hello  " << checker << endl;
            isclicked = C->getIsClicked();
            getmov = C->getMov();
            
            if (SDL_HasIntersection(&spaceship_loc, &getmov))
            {
                if (!isclicked)
                {
                    if (checker == "7Diamond")
                    {
                        C->setIsClicked();      // change status to obtained
                        C->removeCollectible(); // remove collectible from screen
                        totalHealth.updateGems();
                    }
                    else
                    {
                        C->setIsClicked();                             // change status to obtained
                        C->removeCollectible();                        // remove collectible from screen
                        totalHealth.updateHealth(1); // increase user health by 1 point
                    }
                }
            }
        }
    }
}



void SpaceX::displayScore()
{
    // Score is already updated.
    // Current Score can be retrieved using totalScore.getScore()
   
    TTF_Init();
    // Initialize SDL_ttf
    // this opens a font style and sets a size
    TTF_Font *font = TTF_OpenFont("arial.ttf", 28);

    
    SDL_Color color = {255, 255, 255};

    
    std::string score_text = std::to_string(totalScore.getScore());
    SDL_Surface *surfaceMessage =
        TTF_RenderText_Solid(font, score_text.c_str(), color);

    SDL_Texture *Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);

    SDL_Rect Message_rect; 
    Message_rect.x = 1100; 
    Message_rect.y = 60;   
    Message_rect.w = 50;   
    Message_rect.h = 50;   

    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);

    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(font);

    TTF_Quit();
}

void SpaceX::displayHealth()
{
    if (totalHealth.getHealth() >= 0) // if game not over essentially
    {
        SDL_Rect src = {564, 112, 53, 47};
        SDL_Rect mover = {1100, 300, 50, 50};
        for (int i = 0; i < totalHealth.getHealth(); i++)
        {
            if (i % 3 == 0)
            { // positioning of health icons on screen
                mover.x = 1100;
                mover.y += 40;
            }
            SDL_RenderCopy(gRenderer, assets, &src, &mover);
            mover.x += 20;
        }
    }
    if (totalHealth.getGems() >= 0) // if game not over essentially
    {
        SDL_Rect srcGem = {553, 256, 67, 57};
        SDL_Rect moverGem = {1100, 150, 50, 50};
        for (int i = 0; i < totalHealth.getGems(); i++)
        {
            if (i % 3 == 0)
            { // positioning of health icons on screen
                moverGem.x = 1100;
                moverGem.y += 40;
            }
            SDL_RenderCopy(gRenderer, assets, &srcGem, &moverGem);
            moverGem.x += 20;
        }
    }
}

void SpaceX::drawObjects()
{
    bool isclicked;
    int i = 0;
    int j = 0;
    int k = 0;
    // totalHealth.displayHealth(gRenderer, assets);
    for (auto E : Enemies)
    {
        if (!E->outOfScreen())
        {
            E->draw(gRenderer, assets, E->getSrc() , E->getMov()); // draw enemies on screen
            E->dropEnemies();           // drop them from the top
            isclicked = E->getIsClicked();
            if (isclicked)
            {
                E->animateEnemy();
            }
        }
        else
        {
            list<Enemy *>::iterator it1 = Enemies.begin();
            advance(it1, i);
            Enemies.erase(it1);
            delete E; // if out of screen, delete enemy object
        }
        i++;
    }

    for (auto F : Obstacles) // exactly same function as above for enemies objects
    {
        if (!F->outOfScreen())
        {
            F->draw(gRenderer, assets,F->getSrc(),F->getMov());
            F->dropObstacles();
        }
        else
        {
            list<Obstacle *>::iterator it2 = Obstacles.begin();
            advance(it2, j);
            Obstacles.erase(it2);
            delete F;
        }
    }
    for (auto C : Collectibles) // exactly same functions as above for enemies and obstaces objects
    {
        if (!C->outOfScreen())
        {
            C->draw(gRenderer, assets,C->getSrc(),C->getMov());
            C->dropCollectibles();
        }
        else
        {
            list<Collectible *>::iterator it3 = Collectibles.begin();
            advance(it3, k);
            Collectibles.erase(it3);
            delete C;
        }
    }
}
void SpaceX::drawSpaceship() // function to draw chosen spaceship
{
    bool Collision;
    spaceship_in_game->draw(gRenderer, assets);
}

Spaceship *SpaceX::getSpaceship() // function to return pointer of the spaceship object
{
    return spaceship_in_game;
}



void SpaceX::createObject() // function to make spacehsip
{
    int randomObject, randomEnemy, randomObstacle, randomCollectible, randomX;
    srand(time(0));
    randomX = 1 + rand() % 10;
    randomX = 100 * randomX;
    

    SDL_Rect objectMov = {randomX, 10, 75, 90};

    randomObject = 1 + rand() % 100;
    if (randomObject < 50)
    {
        randomObstacle = rand() % 2;
        if (randomObstacle == 0)
        {
            Obstacles.push_back(new BlueAsteroid(gRenderer, assets, objectMov));
            
        }
        
         else if (randomObstacle == 1)
         {
             Obstacles.push_back(new RedAsteroid(gRenderer, assets, objectMov));
             
        }
        
    }
    else if (randomObject < 86)
    {

        Enemie_factory obj;
        Enemies.push_back(obj.getObject());

        
    }
    else
    {
        randomCollectible = rand() % 2;
        if (randomCollectible == 0)
        {
            Collectibles.push_back(new Health(gRenderer, assets, objectMov));
            
        }
        else if (randomCollectible == 1)
        {
            Collectibles.push_back(new Diamond(gRenderer, assets, objectMov));
            
        }
    }
}




void SpaceX::createSpaceship(int spaceship)
{
    SDL_Rect spaceship_mover = {400, 570, 100, 100};
    spaceship_in_game = new Spaceship(gRenderer, assets, spaceship_mover, spaceship);
}
SpaceX::SpaceX(SDL_Renderer *renderer, SDL_Texture *asst, Score &totalScore, HealthPoints &totalHealth) : gRenderer(renderer), assets(asst), totalScore(totalScore), totalHealth(totalHealth)
{
}

// Deconstructor deletes all objects of Tanks and Bullets from list and clears all pointers

SpaceX::~SpaceX()
{
    
    for (auto E : Enemies)
    {
        delete E;
    }
    for (auto F : Obstacles)
    {
        delete F;
    }
    for (auto C : Collectibles)
    {
        delete C;
    }
    delete spaceship_in_game;
    spaceship_in_game = NULL;
    Collectibles.clear();
    Obstacles.clear();
    Enemies.clear();
    std::cout << "Objects deleted";
}