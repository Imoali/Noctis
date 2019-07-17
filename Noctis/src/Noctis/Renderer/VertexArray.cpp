#include "ntpch.h"
#include "VertexArray.h"
#include "Noctis/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Noctis {
	VertexArray * VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
		{
			NT_CORE_ASSERT(false, "Renderer API isn't set!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return new OpenGLVertexArray();
		}
		}
		NT_CORE_ASSERT(false, "Renderer API isn't known!");
		return nullptr;
	}
}
