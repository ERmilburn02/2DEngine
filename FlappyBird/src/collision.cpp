#include "collision.hpp"

namespace FB
{
    bool checkCollision(int x1, int y1, int h1, int w1, int x2, int y2, int w2, int h2)
    {
        if (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2)
            return true;

        return false;
    }

    bool checkPipeCollision(int birdX, int birdY, int pipeX, int pipeGap, int windowHeight)
    {
        return checkCollision(birdX, birdY, 16, 16, pipeX, 0, 32, pipeGap - 48) ||
               checkCollision(birdX, birdY, 16, 16, pipeX, pipeGap + 48, 32, windowHeight);
    }
} // namespace FB
