#include <iostream>
#include "MainMenu.hpp"

void MainMenu::createObject(int x, int y)
{
    std::cout << "Mouse clicked at: " << x << " -- " << y << std::endl;
}

MainMenu::MainMenu(SDL_Renderer *renderer, SDL_Texture *asst) : gRenderer(renderer), assets(asst)
{
}

// Deconstructor deletes all objects of objects and Bullets from list and clears all pointers

MainMenu::~MainMenu()
{
    std::cout << "Objects deleted";
}