#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Game
{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1200; //defining our screen dimensions
    const int SCREEN_HEIGHT = 700;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The window renderer
    SDL_Renderer *gRenderer = NULL;

     //The music that will be played
    Mix_Music *gMusic = NULL;

    //Current displayed texture
    SDL_Texture *gTexture = NULL;
    
    SDL_Texture *assets = NULL;

public:
    //static Game* obj;
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture *loadTexture(std::string path);
    void run();
};
