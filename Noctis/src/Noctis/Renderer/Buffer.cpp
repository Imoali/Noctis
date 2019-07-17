#include "ntpch.h"
#include "buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Noctis {
	VertexBuffer * VertexBuffer::Create(float * vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				{
					NT_CORE_ASSERT(false, "Renderer API isn't set!");
					return nullptr; 
				}
			case RendererAPI::API::OpenGL:
				{
					return new OpenGLVertexBuffer(vertices, size); 
				}
		}
		NT_CORE_ASSERT(false, "Renderer API isn't known!");
		return nullptr;
	}


	IndexBuffer * IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
		{
			NT_CORE_ASSERT(false, "Renderer API isn't set!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return new OpenGLIndexBuffer(indices, count);
		}
		}
		NT_CORE_ASSERT(false, "Renderer API isn't known!");
		return nullptr;
	}
}