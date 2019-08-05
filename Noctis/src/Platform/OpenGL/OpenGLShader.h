#pragma once
#include "Noctis/Renderer/Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Noctis {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformInt(const std::string& name, const int& vector);
		void UploadUniformFloat(const std::string& name, const float& vector);
		void UploadUniformVec2(const std::string& name, const glm::vec2& vector);
		void UploadUniformVec3(const std::string& name, const glm::vec3& vector);
		void UploadUniformVec4(const std::string& name, const glm::vec4& vector);

		uint32_t GetRenderer() const {
			return m_RendererID;
		}
	private:
		uint32_t m_RendererID;
	};
}
