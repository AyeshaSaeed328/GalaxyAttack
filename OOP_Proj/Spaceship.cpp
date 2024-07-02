#include "Spaceship.hpp"

Spaceship::Spaceship(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov, int spaceship) : gRenderer(rend), assets(ast)
{ //defining coordinates for each spaceship from the assets file
    mover = mov;
    spaceship_type = spaceship;
    if (spaceship == 1)
    {
        src = {431, 264, 105, 107};
    }
    else if (spaceship == 2)
    {
        src = {302, 262, 100, 104};
    }
    else if (spaceship == 3)
    {
        src = {169, 250, 89, 121};
    }
    else if (spaceship == 4)
    {
        src = {15, 257, 94, 108};
    }
    else if (spaceship == 5)
    {
        src = {110, 123, 90, 103};
    }
    
}

void Spaceship::draw(SDL_Renderer *gRenderer, SDL_Texture *assets) //drwaing the spacehship
{
    if (!bullets.empty()){
        restTime+=1;
    }
    SDL_RenderCopy(gRenderer, assets, &src, &mover);
    int i=0;
    for (auto B :  bullets){
        if (!B->outOfScreen()){
            B->draw(gRenderer,assets);
            ++(*B); //operator overloading for bullets which moves them
        }else{
            list<Bullets*>::iterator it = bullets.begin();
            advance(it,i);
            bullets.erase(it);
            delete B;
        }
        i++;
    }
}

void Spaceship::operator ++ (){ //operator overloading for horizontal movement
    if(mover.x>1){
        mover.x -= 50;
    }
}

void Spaceship::operator ++ (int y){ //operator overloading for horizontal movement
    if(mover.x<1100){
        mover.x += 50;
    }
}

void Spaceship::blastAnimation() {}

void Spaceship::createBullets() //creating bullets for the spaceship when spacebar is pressed
{
    if (bullets.empty()){
        bullets.push_back(new Bullets(gRenderer, assets, mover, spaceship_type));
    }else{
    if (restTime>5){
        bullets.push_back(new Bullets(gRenderer, assets, mover, spaceship_type));
        restTime=0;
    }
    }
}

void Spaceship::Fire() {}

SDL_Rect Spaceship::getMov() //movement checker
{
    return mover;
}

bool Spaceship::getCollision() {}

void Spaceship::setCollision() {}

Spaceship::~Spaceship() //destructor destroying the spaceship when game ended
{
    for (auto B : bullets){
        delete B;
    }
    bullets.clear();
}

list<Bullets*> Spaceship::getBullets() //list of bullets fired
{
    return bullets;
}