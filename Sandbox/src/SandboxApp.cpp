#include "2DEngine.hpp"

// #include "raylib.h"

int main(void)
{
    Engine::Window window(960, 540, "Sandbox");
    window.SetWindowFPS(60);

    Engine::Texture raylogo("data/global/textures/raylib-logo.png");

    window.SetShowFPS(true);

    int offset = 256 / 2;

    while (!window.shouldClose())
    {
        auto deltaTime = window.getDeltaTime();
        auto mx = window.getMouseX();
        auto my = window.getMouseY();
        window.Begin();
        window.Clear(true);
        window.Draw(raylogo, mx - offset, my - offset);
        window.End();
    }
}