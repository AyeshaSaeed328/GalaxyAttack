#include "Bullets.hpp"

void Bullets::draw(SDL_Renderer *rend, SDL_Texture *ast){
        SDL_RenderCopy(gRenderer, assets, &srcB, &moverB);
}

void Bullets::operator ++(){ //operator overloading function for movement of bullet
    moverB.y-=20; // moverB.y moves 20 pixels up the screen.
}

SDL_Rect Bullets::getLocation() //bullet location
{
    return moverB;
}

void Bullets::removeBullet() //making the bullet null
{
    moverB.h=0;moverB.w=0; 
}

bool Bullets::outOfScreen(){ //checking if the bullet is out of screen
    if ((moverB.y+moverB.h)<0){
        return true;
    }else{
        return false;
    }
}

Bullets::Bullets(SDL_Renderer *rend, SDL_Texture *ast, SDL_Rect mov, int bullet_type):gRenderer(rend), assets(ast)
{ // speed of each bullet is defined and we have generated its co-ordinates.
    if (bullet_type == 1){
        moverB = {mov.x+30,mov.y-25,40,40};
        srcB = {642, 221, 15, 10}; 
    }
    else if (bullet_type == 2){
        moverB = {mov.x+35,mov.y-20,30,40};
        srcB = {643, 190, 13, 11}; 
    }
    else if (bullet_type == 3){
        moverB = {mov.x,mov.y-40,100,70};
        srcB = {645,136, 9, 7}; 
    }
    else if (bullet_type == 4){
        moverB = {mov.x,mov.y-25,100,70};
        srcB = {645,136, 9, 7}; 
    }
    else if (bullet_type == 5){
        moverB = {mov.x+35,mov.y-25,30,40};
        srcB = {645,136, 9, 7}; 
    }
    
}