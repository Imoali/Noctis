#include "ntpch.h"
#include "Application.h"

#include "Noctis/Events/Event.h"
#include "Noctis/Events/ApplicationEvent.h"
#include "Noctis/Log.h"
#include "GLFW/glfw3.h"

namespace Noctis {

	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window> (Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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
		NT_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.m_handled) {
				break;
			}
		}
	};


	void Application::Run() {
		while (m_Running) {
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			//update layers
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			//update window
			m_Window->OnUpdate();
		};
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	};

}