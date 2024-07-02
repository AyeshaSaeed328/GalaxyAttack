#include "game.hpp"
#include <vector>
using namespace std;

int main(int argc, char *argv[]) //main function where the game is started, run and closed
{
    Game game;
    
    srand(time(NULL));
    if (!game.init())
    {
        printf("Failed to initialize!\n");
        return 0;
    }
    //Load media
    if (!game.loadMedia())
    {
        printf("Failed to load media!\n");
        return 0;
    }
    game.run();
    game.close();

    return 0;
}