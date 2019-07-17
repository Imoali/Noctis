#pragma once
#include "Noctis/Renderer/RendererAPI.h"

namespace Noctis {

	class OpenGLRendererAPI : public RendererAPI {
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4 & color) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}