#include "2DEngine.hpp"

int main(int argc, char **argv)
{
    Engine::Window window(960, 540, "Pong");
    window.SetWindowFPS(60);
    window.SetShowFPS(true);
    Engine::Texture raylibLogo("data/global/textures/raylib-logo.png");

    while (!window.shouldClose())
    {
        auto deltaTime = window.getDeltaTime();
        window.Begin();
        window.Clear(false);
        window.End();
    }

    return 0;
}