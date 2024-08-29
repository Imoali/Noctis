#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Noctis {

std::shared_ptr<Texture> Texture::Create(const std::string& path) {
    return std::make_shared<OpenGLTexture>(path);
}

}
