#include <SDL.h>
using namespace std;
class MainMenu
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;

public:
    MainMenu(SDL_Renderer *, SDL_Texture *);
    void createObject(int, int);
    ~MainMenu();
};