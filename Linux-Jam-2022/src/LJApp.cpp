#include "2DEngine.hpp"

int main(int argc, char **argv)
{
    Engine::Window window(960, 540, "Linux Jam 2022");
    window.SetWindowFPS(60);
    window.SetShowFPS(true);

    // TODO: Load resources

    while (!window.shouldClose())
    {
        window.Begin();
        window.Clear(false);

        // TODO: Update

        // TODO: Render

        window.End();
    }

    return 0;
}