#include "ntpch.h"
#include "Shader.h"
#include "Noctis/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Noctis {
	Shader * Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
		{
			NT_CORE_ASSERT(false, "Renderer API isn't set!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		}
		NT_CORE_ASSERT(false, "Renderer API isn't known!");
		return nullptr;
	}
}