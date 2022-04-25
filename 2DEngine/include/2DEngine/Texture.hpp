#pragma once
#include <string>
#include <raylib.h>

namespace Engine
{

    class Texture
    {
    public:
        Texture(const std::string &path);
        ~Texture();

        inline Texture2D GetTexture() const { return m_Texture; }

    private:
        Texture2D m_Texture;
        std::string m_TexturePath;
    };

} // namespace Engine
