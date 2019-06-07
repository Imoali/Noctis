#pragma once

#include "Core.h"

namespace Noctis {

	class NOCTIS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();
}
	