#include "ntpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Noctis {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
