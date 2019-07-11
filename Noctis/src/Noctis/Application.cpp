#include "ntpch.h"
#include "Application.h"
#include "Noctis/Log.h"
#include "Input.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Noctis {

	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

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

	Application::Application()
	{
		NT_CORE_ASSERT(!s_Instance, "Failed only One Instance of app should exist!")
			s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		//OPENGL RENDERING TRIANGLE
		glGenVertexArrays(0, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			BufferLayout layout = {
						{ShaderDataType::Float3, "a_Position"},
						{ShaderDataType::Float4, "a_Color"},
			};
			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.m_Type), 
				element.m_Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), (const void*)element.m_Offset);
			index++;
		}


		unsigned int indices[] = { 0, 1, 2 };

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	
		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;
			void main(){
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0); 
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			in vec4 v_Color;
			layout (location = 0) out vec4 FragColor;
  
			void main()
			{
				FragColor = v_Color;
			} 
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay){
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.m_handled) {
				break;
			}
		}
	};


	void Application::Run() {
		uint32_t Program = m_Shader->GetRenderer();
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			//update layers
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->end();

			//update window
			m_Window->OnUpdate();
		};
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	};

}