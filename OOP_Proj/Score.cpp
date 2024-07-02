#include "Score.hpp"
#include <iostream>

Score::Score(int initialScore) : S(initialScore) {}

void Score::ScoreUpdate() //score update on collision
{
    S += 10;
}

int Score::getScore() //getting the score
{
    return S;
}