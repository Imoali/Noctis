// OpenGLTexture.h
#pragma once

#include "Noctis/Renderer/Texture.h"

namespace Noctis {

class OpenGLTexture : public Texture {
public:
    OpenGLTexture(const std::string& path);
    ~OpenGLTexture();

    void Bind(unsigned int slot = 0) const override;
    void Unbind() const override;

    unsigned int GetWidth() const override { return m_Width; }
    unsigned int GetHeight() const override { return m_Height; }

private:
    std::string m_Path;
    unsigned int m_RendererID;
    unsigned int m_Width, m_Height;
    unsigned char* m_LocalBuffer;
};

}
