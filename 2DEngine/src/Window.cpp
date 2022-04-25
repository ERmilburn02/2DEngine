#include "2DEngine/Window.hpp"
#include <raylib.h>

namespace Engine
{

    Window::Window(int x, int y, const std::string &title)
        : m_X(x), m_Y(y), m_Title(title)
    {
        InitWindow(m_X, m_Y, m_Title.c_str());
        SetExitKey(KEY_NULL);
    }

    Window::~Window()
    {
        CloseWindow();
    }

    bool Window::shouldClose()
    {
        return WindowShouldClose();
    }

    float Window::getDeltaTime()
    {
        return GetFrameTime();
    }

    int Window::getMouseX()
    {
        return GetMouseX();
    }

    int Window::getMouseY()
    {
        return GetMouseY();
    }

    void Window::SetWindowFPS(int fps)
    {
        SetTargetFPS(fps);
    }

    int Window::GetWindowFPS()
    {
        return GetFPS();
    }

    void Window::Begin() const
    {
        BeginDrawing();
    }

    void Window::End() const
    {
        // TODO: Is there a better place to draw FPS?
        if (m_ShouldShowFPS)
            DrawFPS(10, 10);

        EndDrawing();
    }

    void Window::Clear(bool background) const
    {
        ClearBackground(background ? RAYWHITE : BLANK);
    }

    void Window::Draw(const Engine::Texture &tex, int x, int y) const
    {
        DrawTexture(tex.GetTexture(), x, y, WHITE);
    }

    void Window::Draw(const Engine::Texture &tex, int x, int y, float scale) const
    {
        DrawTextureEx(tex.GetTexture(), (Vector2){(float)x, (float)y}, 0, scale, WHITE);
    }

    void Window::SetShowFPS(bool value)
    {
        m_ShouldShowFPS = value;
    }

} // namespace Engine