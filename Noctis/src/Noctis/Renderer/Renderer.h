#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Noctis/Renderer/Shader.h"

namespace Noctis {

	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjetionMatrix;
		};
		static SceneData* s_SceneData;
	};

}