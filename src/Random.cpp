#include "Random.h"

Random::Random()
{
    srand(std::time(nullptr));
}

Random::~Random() { }
