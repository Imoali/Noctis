#pragma once

#ifdef NT_PLATFORM_WINDOWS
extern Noctis::Application* Noctis::CreateApplication();
int main(int argc, char** argv) {

	auto app = Noctis::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif
