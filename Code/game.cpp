#include "game.hpp"
// #include "MainMenu.hpp"
#include <vector>
#include "SpaceX.hpp"
#include "Score.hpp"
#include "HealthPoints.hpp"
#include "Spaceship.hpp"
#include <time.h>
bool Game::init() //this is our game initliaziting function 
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                // Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool Game::loadMedia() //this function will load all our media including our main menu screen, playing screen, assests and sounds.
{
    // Loading success flag
    bool success = true;

    assets = loadTexture("assets.png"); //getting assests
    gTexture = loadTexture("mainmenu.jpeg"); //getting our mainmenu screen
    if (assets == NULL || gTexture == NULL)
    {
        printf("Unable to run due to error: %s\n", SDL_GetError());
        success = false;
    }
    gMusic = Mix_LoadMUS("bg_music.mp3"); //getting the background music
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void Game::close() //this function would close the game.
{
    // Free loaded images
    SDL_DestroyTexture(assets);
    assets = NULL;

    SDL_DestroyTexture(gTexture);

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
    IMG_Quit();
    SDL_Quit();
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
}

SDL_Texture *Game::loadTexture(std::string path)
{

    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void Game::run() //this is the most important function of out game class which helps in the dynamicity and running of our game

{
    int level=0;
    bool quit = false;
    SDL_Event e;
    static int Screen = 0;
    if (Screen != 6)
    {
        Mix_PlayMusic(gMusic, -2);
    }
    Score totalScore(0); //initializing score
    HealthPoints totalHealth(3); //initializing health
    SpaceX SpaceX(gRenderer, assets, totalScore, totalHealth); //initiliazing our game screen
    bool objectCreated = false;
    int frameCounter = 0;
    // MainMenu MainMenu(gRenderer, assets);
    while (!quit)
    {
        
        while (SDL_PollEvent(&e) != 0)
        {

            int xMouse, yMouse;
            
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {

                SDL_GetMouseState(&xMouse, &yMouse);
                std::cout << xMouse << " " << yMouse << std::endl; //outputting our mouse clicks
                if (xMouse >= 265 && xMouse <= 566 && yMouse >= 560 && yMouse <= 680 && Screen == 0) //checking when the levels button is pressed by checking the coordinates
                {
                    Screen = 2;
                    gTexture = loadTexture("Levels.jpeg");
                }
    
                else if (xMouse >= 489 && xMouse <= 694 && yMouse >= 483 && yMouse <= 552 && Screen == 0) //checking when the about button is pressed by checking the coordinates
                {
                    Screen = 1;
                    gTexture = loadTexture("about.jpeg");
                }
                else if (xMouse >= 590 && xMouse <= 840 && yMouse >= 543 && yMouse <= 680 && Screen == 0)  //checking when the how to play button is pressed by checking the coordinates
                {
                    Screen = 3;
                    gTexture = loadTexture("HowToPlay.jpeg");
                }
                else if (xMouse >= 0 && xMouse <= 55 && yMouse >= 0 && yMouse <= 45 && (Screen == 1 || Screen==2 || Screen == 3))  //checking when the console button on the top left is pressed by checking the coordinates
                {
                        gTexture = loadTexture("mainmenu.jpeg");
                        Screen = 0;
                }
                else if (xMouse >= 0 && xMouse <= 55 && yMouse >= 0 && yMouse <= 45 && Screen==4)  //checking when the console button is pressed by checking the coordinates while on screen 4
                {
                        gTexture = loadTexture("Levels.jpeg");
                        Screen = 2;
                }
                else if (xMouse >= 19 && xMouse <= 67 && yMouse >= 26 && yMouse <= 64 && Screen==6) //checking when the console button is pressed by checking the coordinates while on screen 6
                {
                        gTexture = loadTexture("Spaceships.jpeg");
                        Screen = 4;
                }
                else if (xMouse>=406 && xMouse<= 750 && yMouse >= 35 && yMouse<= 210 && Screen ==2) //checking the coordinate for the respective level and then loading the spaceship screen
                {
                    gTexture = loadTexture("Spaceships.jpeg");
                    Screen = 4;
                    level=1;
                }
                else if(xMouse>=406 && xMouse<= 750 && yMouse >= 250 && yMouse<= 425 && Screen ==2)  //checking the coordinate for the respective level and then loading the spaceship screen
                {
                    gTexture = loadTexture("Spaceships.jpeg");
                    Screen = 4;
                    level=2;
                }
                else if(xMouse>=406 && xMouse<= 750 && yMouse >= 470 && yMouse<= 645 && Screen ==2) //checking the coordinate for the respective level and then loading the spaceship screen
                {
                    gTexture = loadTexture("Spaceships.jpeg");
                    Screen = 4;
                    level=3;
                }

                //the next set of else if statements would check that which spaceship is selected by checking the coordinate of each spaceship and then loading the main playing screen
                else if (xMouse >= 340 && xMouse <= 540 && yMouse >= 145 && yMouse <= 370 && Screen == 4)
                {
                    //Spaceship 1
                    gTexture = loadTexture("SpaceX.png");
                    Screen = 6;
                    SpaceX.createSpaceship(1);
                }
                else if (xMouse >= 722 && xMouse <= 935 && yMouse >= 165 && yMouse <= 360 && Screen == 4)
                {
                    //Spaceship 2
                    gTexture = loadTexture("SpaceX.png");
                    Screen = 6;
                    SpaceX.createSpaceship(3);
                }
                else if (xMouse >= 130 && xMouse <= 345 && yMouse >= 370 && yMouse <= 600 && Screen == 4)
                {
                    //Spaceship 3
                    gTexture = loadTexture("SpaceX.png");
                    Screen = 6;
                    SpaceX.createSpaceship(2);
                }
                else if (xMouse >= 560 && xMouse <= 740 && yMouse >= 370 && yMouse <= 590 && Screen == 4)
                {
                    //Spaceship 4
                    gTexture = loadTexture("SpaceX.png");
                    Screen = 6;
                    SpaceX.createSpaceship(5);
                }
                else if (xMouse >= 885 && xMouse <= 1095 && yMouse >= 370 && yMouse <= 590 && Screen == 4)
                {
                    //Spaceship 5
                    gTexture = loadTexture("SpaceX.png");
                    Screen = 6;
                    SpaceX.createSpaceship(4);
                }
               

            }
            if (e.type == SDL_KEYDOWN){
                SpaceX.checkMouseClick(xMouse,yMouse, Screen);
                
                if (e.key.keysym.sym == SDLK_ESCAPE && (Screen == 1 || Screen == 2 || Screen == 3))
                {
                    gTexture = loadTexture("Mainmenu.png");
                    Screen = 0;
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE && Screen == 4)
                {
                    gTexture = loadTexture("Levels.png");
                    Screen = 2;
                }
                // pressing space fires the bullets
                if (e.key.keysym.sym == SDLK_SPACE && Screen == 6)
                {
                    SpaceX.getSpaceship()->createBullets();
                }

                //pressing left right arrow keys moves the spaceship
                if (e.key.keysym.sym == SDLK_LEFT && Screen == 6)
                {
                    //operator overloading 
                    ++(*SpaceX.getSpaceship());
                }
                else if(e.key.keysym.sym == SDLK_RIGHT && Screen == 6)
                {
                    //operator overloading
                    (*SpaceX.getSpaceship())++;
                }
            }
        }
        if (Screen == 6)
        {
            srand(time(0));
            int randomWait;
            randomWait = rand() % 2;
            //checking if there is any object created on the game screen
            if (objectCreated == false)
            {
                // SDL_Delay(100);
                SpaceX.createObject();
                objectCreated = true;
                // SpaceX.artificialDelay();
            }
        } 
        //at the end displaying the game over screen 
        if (Screen == 7)
        {
            gTexture = loadTexture("GameOver.png");
        }

        SDL_RenderClear(gRenderer);                      // removes everything from renderer
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); // Draws background to renderer
        //***********************draw the objects here********************
        if (Screen >= 6)
        {
            SpaceX.drawSpaceship();
            SpaceX.drawObjects();
            SpaceX.displayScore();
            SpaceX.displayHealth();
            SpaceX.deleteObjects();
        }
        // MainMenu.drawObjects();

        //****************************************************************
        SDL_RenderPresent(gRenderer); // displays the updated renderer

        if(level==1){
            SDL_Delay(150);
        }

        else if(level==2){
            SDL_Delay(100);
        }

        else if(level==3){
            SDL_Delay(50);
        }

        //SDL_Delay(100); // causes sdl engine to delay for specified miliseconds
        frameCounter += 1;
        if (frameCounter == 15)
        {
            objectCreated = false;
            frameCounter = 0;
        }
}
}