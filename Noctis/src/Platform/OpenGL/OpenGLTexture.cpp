// OpenGLTexture.cpp
#include "OpenGLTexture.h"
#include <glad/glad.h>

namespace Noctis {

OpenGLTexture::OpenGLTexture(const std::string& path)
    : m_Path(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_RendererID(0) {
    // TODO Load the texture
}

OpenGLTexture::~OpenGLTexture() {
    glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture::Bind(unsigned int slot) const {
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void OpenGLTexture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
