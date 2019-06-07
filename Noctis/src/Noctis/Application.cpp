#include "Application.h"

#include "Noctis/Events/Event.h"
#include "Noctis/Events/ApplicationEvent.h"
#include "Noctis/Log.h"

namespace Noctis {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizeEvent e(120, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			NT_CLIENT_TRACE(e);
		}
		while (true);	
	}
}