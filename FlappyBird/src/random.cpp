#include "random.hpp"

#include <stdio.h>  /* NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

namespace FB
{
    void seedRandom()
    {
        srand(time(NULL));
    }

    void seedRandom(unsigned int seed)
    {
        srand(seed);
    }

    int random(int min, int max)
    {
        int diff = max - min;
        return rand() % diff + min;
    }
} // namespace FB
