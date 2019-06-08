#include "ntpch.h"
#include "Application.h"

#include "Noctis/Events/Event.h"
#include "Noctis/Events/ApplicationEvent.h"
#include "Noctis/Log.h"

namespace Noctis {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window> (Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		};
	}
}