// Texture.h
#pragma once

#include <string>
#include <memory>
#include "Noctis/Renderer/Renderer.h"

namespace Noctis {

class Texture {
public:
    virtual ~Texture() = default;

    virtual void Bind(unsigned int slot = 0) const = 0;
    virtual void Unbind() const = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    static std::shared_ptr<Texture> Create(const std::string& path);
};

}
