#pragma once
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Noctis{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		uint32_t GetRenderer() const {
			return m_RendererID;
		}
	private:
		uint32_t m_RendererID;
	};
}
