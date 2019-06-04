#pragma once

#include "Core.h"

namespace Noctis {

	class Noctis_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();
}
	