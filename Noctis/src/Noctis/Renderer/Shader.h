#pragma once
#include <string>

namespace Noctis{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		uint32_t GetRenderer() const {
			return m_RendererID;
		}
	private:
		uint32_t m_RendererID;
	};
}
