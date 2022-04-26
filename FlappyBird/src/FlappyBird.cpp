#include "2DEngine.hpp"

#include "random.hpp"
#include "collision.hpp"

#include <string>

#include "raylib.h" // TODO: Remove

#define WINDOW_SCALE 2
#define WINDOW_WIDTH 256 * 2
#define WINDOW_HEIGHT 256

void drawBackgrounds(const Engine::Window &window, const Engine::Texture &texture, int offset)
{
    window.Draw(texture, 0 * 256 * WINDOW_SCALE + offset, 0, WINDOW_SCALE);
    window.Draw(texture, 1 * 256 * WINDOW_SCALE + offset, 0, WINDOW_SCALE);
    window.Draw(texture, 2 * 256 * WINDOW_SCALE + offset, 0, WINDOW_SCALE);
}

void drawPipe(const Engine::Window &window, const Engine::Texture &pipeTop, const Engine::Texture &pipeMiddle, const Engine::Texture &pipeBottom, int x, int yGap)
{
    for (int t = 0; t < yGap - 48; t += 16)
    {
        window.Draw(pipeMiddle, x * WINDOW_SCALE, t * WINDOW_SCALE, WINDOW_SCALE);
    }
    for (int t = WINDOW_HEIGHT; t > yGap + 48; t -= 16)
    {
        window.Draw(pipeMiddle, x * WINDOW_SCALE, t * WINDOW_SCALE, WINDOW_SCALE);
    }
    window.Draw(pipeTop, x * WINDOW_SCALE, (yGap + 48) * WINDOW_SCALE, WINDOW_SCALE);
    window.Draw(pipeBottom, x * WINDOW_SCALE, (yGap - 48) * WINDOW_SCALE, WINDOW_SCALE);
}

void drawFloor(const Engine::Window &window, const Engine::Texture &texture, int offset)
{
    for (int x = 0; x < ((WINDOW_WIDTH / 256) + 1) * 256; x += 16)
    {
        window.Draw(texture, WINDOW_SCALE + offset + (x * WINDOW_SCALE), WINDOW_HEIGHT * WINDOW_SCALE - (16 * WINDOW_SCALE), WINDOW_SCALE);
    }
}

void drawSplashScreen(const Engine::Window &window, const Engine::Texture &raylibLogo)
{
    window.Draw(raylibLogo, 128, 128);
    auto sw = MeasureText("Flappy Bird", 48);
    // DrawText("Flappy Bird", WINDOW_WIDTH + (sw / 2) - 20, 192, 48, WHITE);
    DrawText("Flappy Bird", (WINDOW_WIDTH / 4 * 3) * WINDOW_SCALE - sw / 2, 192, 48, WHITE);
    auto sw2 = MeasureText("By ERmilburn02", 44);
    DrawText("By ERmilburn02", WINDOW_WIDTH + (sw2 / 4), 320, 44, RAYWHITE);
}

void DrawGameOver(const Engine::Window &window)
{
    auto sw = MeasureText("Game Over!", 72);
    DrawText("Game Over!", (WINDOW_WIDTH / 2) * WINDOW_SCALE - sw / 2, (WINDOW_HEIGHT / 2) * WINDOW_SCALE, 72, BLACK);
    auto sw2 = MeasureText("Press Enter to restart", 48);
    DrawText("Press Enter to restart", (WINDOW_WIDTH / 2) * WINDOW_SCALE - sw2 / 2, (WINDOW_HEIGHT / 2) + 125 * WINDOW_SCALE, 48, BLACK);
}

int main(int argc, char **argv)
{
    Engine::Window window(WINDOW_WIDTH * WINDOW_SCALE, WINDOW_HEIGHT * WINDOW_SCALE, "Flappy Bird");
    window.SetWindowFPS(60);
    window.SetShowFPS(true);

    // TODO: Load resources
    Engine::Texture background("data/FlappyBird/megacrash/Sprites/Backgrounds/Background2.png");
    Engine::Texture bird("data/FlappyBird/megacrash/Sprites/Player/Player1.png");
    Engine::Texture pipeTop("data/FlappyBird/megacrash/Sprites/Pipes/Pipe1.png");
    Engine::Texture pipeMiddle("data/FlappyBird/megacrash/Sprites/Pipes/Pipe5.png");
    Engine::Texture pipeBottom("data/FlappyBird/megacrash/Sprites/Pipes/Pipe9.png");
    Engine::Texture floor("data/FlappyBird/megacrash/Sprites/Tiles/Tile2.png");
    Engine::Texture raylibLogo("data/global/textures/raylib-logo.png");

    // TODO: Global vars
    int backgroundOffset = 0;
    int birdHeight = 128;
    const int birdXPos = 64;
    int birdVelocity = 0;

    const int gravity = 25;

    bool inputEnabled = false;
    bool gravityEnabled = false;
    bool birdMoving = true;

    bool showSplashScreen = true;

    FB::seedRandom();

    int pipeX1 = WINDOW_WIDTH + 128 * 1;
    int pipeX2 = WINDOW_WIDTH + 128 * 2;
    int pipeX3 = WINDOW_WIDTH + 128 * 3;
    int pipeX4 = WINDOW_WIDTH + 128 * 4;
    int pipeX5 = WINDOW_WIDTH + 128 * 5;
    int pipeX6 = WINDOW_WIDTH + 128 * 6;
    int pipeY1 = FB::random(96, WINDOW_HEIGHT - 96);
    int pipeY2 = FB::random(96, WINDOW_HEIGHT - 96);
    int pipeY3 = FB::random(96, WINDOW_HEIGHT - 96);
    int pipeY4 = FB::random(96, WINDOW_HEIGHT - 96);
    int pipeY5 = FB::random(96, WINDOW_HEIGHT - 96);
    int pipeY6 = FB::random(96, WINDOW_HEIGHT - 96);
    bool ps1 = true, ps2 = true, ps3 = true, ps4 = true, ps5 = true, ps6 = true;

    int score = 0;
    float splashTimeout = 3.0f;

    bool dead = false;

    bool reset = false;

    float pipeSpeed = 1.0f;

    while (!window.shouldClose())
    {
        auto deltaTime = window.getDeltaTime();

        window.Begin();
        window.Clear(false);

        if (reset)
        {
            reset = false;

            backgroundOffset = 0;
            birdHeight = 128;
            birdVelocity = 0;

            inputEnabled = true;
            gravityEnabled = false;
            birdMoving = true;

            FB::seedRandom();

            pipeX1 = WINDOW_WIDTH + 128 * 1;
            pipeX2 = WINDOW_WIDTH + 128 * 2;
            pipeX3 = WINDOW_WIDTH + 128 * 3;
            pipeX4 = WINDOW_WIDTH + 128 * 4;
            pipeX5 = WINDOW_WIDTH + 128 * 5;
            pipeX6 = WINDOW_WIDTH + 128 * 6;
            pipeY1 = FB::random(96, WINDOW_HEIGHT - 96);
            pipeY2 = FB::random(96, WINDOW_HEIGHT - 96);
            pipeY3 = FB::random(96, WINDOW_HEIGHT - 96);
            pipeY4 = FB::random(96, WINDOW_HEIGHT - 96);
            pipeY5 = FB::random(96, WINDOW_HEIGHT - 96);
            pipeY6 = FB::random(96, WINDOW_HEIGHT - 96);
            ps1 = true;
            ps2 = true;
            ps3 = true;
            ps4 = true;
            ps5 = true;
            ps6 = true;

            score = 0;

            dead = false;

            pipeSpeed = 1;
        }

        if (showSplashScreen)
        {
            drawSplashScreen(window, raylibLogo);
            splashTimeout -= deltaTime;
            if (splashTimeout <= 0)
            {
                showSplashScreen = false;
                inputEnabled = true;
            }
        }
        else
        {

            // TODO: Update
            if (birdMoving)
            {
                backgroundOffset -= (int)(deltaTime * 100);
                backgroundOffset %= 256 * WINDOW_SCALE;
            }

            // TODO: Input in engine
            if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(0)) && !gravityEnabled)
            {
                // Start game
                gravityEnabled = true;
            }

            if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(0)) && inputEnabled && gravityEnabled)
            {
                birdVelocity = -(gravity * 6);
            }
            else if (gravityEnabled)
            {
                birdVelocity += gravity;
            }

            // Update pipes
            if (gravityEnabled && birdMoving)
            {
                pipeSpeed += 0.00005f;

                pipeX1 -= (int)(pipeSpeed * deltaTime * 100);
                if (FB::checkPipeCollision(birdXPos, birdHeight, pipeX1, pipeY1, WINDOW_HEIGHT))
                {
                    inputEnabled = false;
                    birdMoving = false;
                }
                if (pipeX1 < -128)
                {
                    pipeX1 += (WINDOW_WIDTH + 256);
                    pipeY1 = FB::random(80, WINDOW_HEIGHT - 80);
                    ps1 = true;
                }
                if (pipeX1 <= birdXPos && ps1)
                {
                    ps1 = false;
                    score++;
                }
                pipeX2 -= (int)(pipeSpeed * deltaTime * 100);
                if (FB::checkPipeCollision(birdXPos, birdHeight, pipeX2, pipeY2, WINDOW_HEIGHT))
                {
                    inputEnabled = false;
                    birdMoving = false;
                }
                if (pipeX2 < -128)
                {
                    pipeX2 += (WINDOW_WIDTH + 256);
                    pipeY2 = FB::random(80, WINDOW_HEIGHT - 80);
                    ps2 = true;
                }
                if (pipeX2 <= birdXPos && ps2)
                {
                    ps2 = false;
                    score++;
                }
                pipeX3 -= (int)(pipeSpeed * deltaTime * 100);
                if (FB::checkPipeCollision(birdXPos, birdHeight, pipeX3, pipeY3, WINDOW_HEIGHT))
                {
                    inputEnabled = false;
                    birdMoving = false;
                }
                if (pipeX3 < -128)
                {
                    pipeX3 += (WINDOW_WIDTH + 256);
                    pipeY3 = FB::random(80, WINDOW_HEIGHT - 80);
                    ps3 = true;
                }
                if (pipeX3 <= birdXPos && ps3)
                {
                    ps3 = false;
                    score++;
                }
                pipeX4 -= (int)(pipeSpeed * deltaTime * 100);
                if (FB::checkPipeCollision(birdXPos, birdHeight, pipeX4, pipeY4, WINDOW_HEIGHT))
                {
                    inputEnabled = false;
                    birdMoving = false;
                }
                if (pipeX4 < -128)
                {
                    pipeX4 += (WINDOW_WIDTH + 256);
                    pipeY4 = FB::random(80, WINDOW_HEIGHT - 80);
                    ps4 = true;
                }
                if (pipeX4 <= birdXPos && ps4)
                {
                    ps4 = false;
                    score++;
                }
                pipeX5 -= (int)(pipeSpeed * deltaTime * 100);
                if (FB::checkPipeCollision(birdXPos, birdHeight, pipeX5, pipeY5, WINDOW_HEIGHT))
                {
                    inputEnabled = false;
                    birdMoving = false;
                }
                if (pipeX5 < -128)
                {
                    pipeX5 += (WINDOW_WIDTH + 256);
                    pipeY5 = FB::random(80, WINDOW_HEIGHT - 80);
                    ps5 = true;
                }
                if (pipeX5 <= birdXPos && ps5)
                {
                    ps5 = false;
                    score++;
                }
                pipeX6 -= (int)(pipeSpeed * deltaTime * 100);
                if (FB::checkPipeCollision(birdXPos, birdHeight, pipeX6, pipeY6, WINDOW_HEIGHT))
                {
                    inputEnabled = false;
                    birdMoving = false;
                }
                if (pipeX6 < -128)
                {
                    pipeX6 += (WINDOW_WIDTH + 256);
                    pipeY6 = FB::random(80, WINDOW_HEIGHT - 80);
                    ps6 = true;
                }
                if (pipeX6 <= birdXPos && ps6)
                {
                    ps6 = false;
                    score++;
                }
            }

            if (birdVelocity >= gravity * 3)
                birdVelocity = gravity * 3;

            birdHeight += birdVelocity * deltaTime;

            if (birdHeight <= 0 + 8)
            {
                // Hit roof
                inputEnabled = false;
                birdMoving = false;
                dead = true;
            }

            if (birdHeight >= 256 - 16 - 8)
            {
                // Hit ground
                inputEnabled = false;
                birdMoving = false;
                dead = true;
                birdHeight = 256 - 16 - 8;
            }

            if (IsKeyPressed(KEY_ENTER) && dead)
            {
                reset = true;
            }

            // TODO: Render
            drawBackgrounds(window, background, backgroundOffset);

            drawPipe(window, pipeTop, pipeMiddle, pipeBottom, pipeX1, pipeY1);
            drawPipe(window, pipeTop, pipeMiddle, pipeBottom, pipeX2, pipeY2);
            drawPipe(window, pipeTop, pipeMiddle, pipeBottom, pipeX3, pipeY3);
            drawPipe(window, pipeTop, pipeMiddle, pipeBottom, pipeX4, pipeY4);
            drawPipe(window, pipeTop, pipeMiddle, pipeBottom, pipeX5, pipeY5);
            drawPipe(window, pipeTop, pipeMiddle, pipeBottom, pipeX6, pipeY6);

            drawFloor(window, floor, backgroundOffset);

            window.Draw(bird, birdXPos * WINDOW_SCALE, birdHeight * WINDOW_SCALE, WINDOW_SCALE);

            std::string s = std::to_string(score);
            auto sw = MeasureText(s.c_str(), 72);
            DrawText(s.c_str(), (WINDOW_WIDTH / 2) * WINDOW_SCALE - sw / 2, 50, 72, BLACK);

            if (dead)
                DrawGameOver(window);
        }

        window.End();
    }

    return 0;
}
