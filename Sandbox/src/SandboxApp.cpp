#include <Noctis.h>
#include "imgui.h"

class ExampleLayer : public Noctis::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.60f, 1.60f, -0.90f, 0.90f) , m_CameraPosition(0.0f)
	{
		//----------OPENGL RENDERING TRIANGLE

		m_VertexArray.reset(Noctis::VertexArray::Create());
		std::shared_ptr<Noctis::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Noctis::IndexBuffer> m_IndexBuffer;

		m_SquareVertexArray.reset(Noctis::VertexArray::Create());   //-------SQUARE
		std::shared_ptr<Noctis::VertexBuffer> m_SquareVertexBuffer; //-------SQUARE
		std::shared_ptr<Noctis::IndexBuffer> m_SquareIndexBuffer;	//-------SQUARE

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		m_VertexBuffer.reset(Noctis::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_SquareVertexBuffer.reset(Noctis::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Noctis::BufferLayout layout = {
					{Noctis::ShaderDataType::Float3, "a_Position"},
					{Noctis::ShaderDataType::Float4, "a_Color"},
		};

		Noctis::BufferLayout squareLayout = {
			{Noctis::ShaderDataType::Float3, "a_Position"},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_SquareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };
		m_IndexBuffer.reset(Noctis::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		unsigned int squareIndices[] = { 0, 1, 2 , 2, 3, 0 };
		m_SquareIndexBuffer.reset(Noctis::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;			

			out vec4 v_Color;
			void main(){
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0); 
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

		std::string squareVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;			

			void main(){
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0); 
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 330 core
			layout (location = 0) out vec4 FragColor; 
			uniform vec4 u_Color;
			void main()
			{
				FragColor = u_Color;
			} 
		)";
		m_Shader.reset(Noctis::Shader::Create(vertexSrc, fragmentSrc));
		m_SquareShader.reset(Noctis::Shader::Create(squareVertexSrc, squareFragmentSrc));
	};

	void OnUpdate(Noctis::Timestep ts) override {

		if (Noctis::Input::IsKeyPressed( NT_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Noctis::Input::IsKeyPressed(NT_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Noctis::Input::IsKeyPressed(NT_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Noctis::Input::IsKeyPressed(NT_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		
		if (Noctis::Input::IsKeyPressed(NT_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Noctis::Input::IsKeyPressed(NT_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Noctis::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Noctis::RenderCommand::Clear();

		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Noctis::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int i = 0; i < 10; ++i) {
			glm::vec3 position = { i * 0.11f, 0.0f, 0.0f};
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
			std::dynamic_pointer_cast<Noctis::OpenGLShader>(m_SquareShader)->UploadUniformVec4("u_Color", glm::vec4(s_RGBColor, 1.0f));
			Noctis::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
		}
		Noctis::Renderer::Submit(m_Shader, m_VertexArray);
		Noctis::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		ImGui::Begin("Material");
		ImGui::Text("Material Settings");
		ImGui::Separator();
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Albedo")) {
			ImGui::ColorPicker3("Albedo", value_ptr(s_RGBColor));
		}
		ImGui::Separator();
		ImGui::End();
	}

	void OnEvent(Noctis::Event& event) override {

	};

private:
	//needed for OpenGL rendering
	std::shared_ptr<Noctis::Shader> m_Shader;
	std::shared_ptr<Noctis::VertexArray> m_VertexArray;

	std::shared_ptr<Noctis::Shader> m_SquareShader;					//-------SQUARE
	std::shared_ptr<Noctis::VertexArray> m_SquareVertexArray;

	Noctis::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;

	glm::vec3 s_RGBColor = glm::vec3(1.0f, 1.0f, 1.0f);
};

class Sandbox : public Noctis::Application {
public:
	Sandbox(){
		PushLayer(new ExampleLayer());
	}
	~Sandbox(){
	}
};

Noctis::Application* Noctis::CreateApplication() {
	return new Sandbox();
}