#pragma once

#include <string>
#include <2DEngine/Texture.hpp>

namespace Engine
{

    class Window
    {
    public:
        Window(int x, int y, const std::string &title);
        ~Window();

        void SetWindowFPS(int fps);
        int GetWindowFPS();
        void SetShowFPS(bool value);

        bool shouldClose();
        float getDeltaTime();

        int getMouseX();
        int getMouseY();

        void Begin() const;
        void Clear(bool background) const;
        void Draw(const Engine::Texture &tex, int x, int y) const;
        void Draw(const Engine::Texture &tex, int x, int y, float scale) const;
        void End() const;

    private:
        int m_X,
            m_Y;
        std::string m_Title;
        bool m_ShouldShowFPS;
    };

} // namespace Engine
