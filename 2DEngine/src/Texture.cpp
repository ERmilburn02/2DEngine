#include "2DEngine/Texture.hpp"

#include <raylib.h>

namespace Engine
{

    Texture::Texture(const std::string &path)
        : m_TexturePath(path)
    {
        m_Texture = LoadTexture(m_TexturePath.c_str());
    }

    Texture::~Texture()
    {
        UnloadTexture(m_Texture);
    }

} // namespace Engine