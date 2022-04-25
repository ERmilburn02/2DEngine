#pragma once

namespace FB
{
    int random(int min, int max);

    // Seed with current time
    void seedRandom();

    // Seed with specified seed
    void seedRandom(unsigned int seed);
} // namespace FB
