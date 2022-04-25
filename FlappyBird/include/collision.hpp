#pragma once

namespace FB
{
    bool checkCollision(int x1, int y1, int h1, int w1, int x2, int y2, int w2, int h2);
    bool checkPipeCollision(int birdX, int birdY, int pipeX, int pipeGap, int windowHeight);
} // namespace FB
