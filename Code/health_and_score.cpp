
#include "health_and_score.hpp"
#include <iostream>

void health_and_score::updateHealth(int h)
{
	if (h == -3)
	{
		totalHealth -= totalHealth;
	}
	else
	{
		totalHealth += h;
	}
}

void health_and_score::health_status(int x)
{
	if (x == 1)
	{
		
	}
	else if (x == 2)
	{
	
	}
}
int health_and_score::getHealth()
{
	return totalHealth;
}

health_and_score::health_and_score(int th) : totalHealth(th)
{
}

void health_and_score::update(SDL_Renderer *renderer, SDL_Texture *asst, int x)
{
	health_status(x); // score will be printed.
	SDL_RenderPresent(gRenderer);
	SDL_Delay(5);
}