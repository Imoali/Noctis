#include "ntpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Noctis {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Noctis::ShaderDataType::Float: return GL_FLOAT;
			case Noctis::ShaderDataType::Float2:return GL_FLOAT;
			case Noctis::ShaderDataType::Float3:return GL_FLOAT;
			case Noctis::ShaderDataType::Float4:return GL_FLOAT;
			case Noctis::ShaderDataType::Int:	return GL_INT;
			case Noctis::ShaderDataType::Int2:	return GL_INT;
			case Noctis::ShaderDataType::Int3:	return GL_INT;
			case Noctis::ShaderDataType::Int4:	return GL_INT;
			case Noctis::ShaderDataType::Mat3:  return GL_FLOAT;
			case Noctis::ShaderDataType::Mat4:  return GL_FLOAT;
			case Noctis::ShaderDataType::Bool:	return GL_BOOL;
		}
		NT_CORE_ASSERT(false, "SHader data type is unknown!");
		return 0;
	};

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		//glBindVertexArray(m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}


	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		NT_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no Layout");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.m_Type),
				element.m_Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.m_Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}