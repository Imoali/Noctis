#pragma once

#ifdef NT_PLATFORM_WINDOWS
extern Noctis::Application* Noctis::CreateApplication();
int main(int argc, char** argv) {
	Noctis::Log::Init();
	NT_CORE_INFO("Starting Noctis Engine!");
	NT_CLIENT_INFO("Starting the application ");
	auto app = Noctis::CreateApplication();
	NT_CLIENT_INFO("Application created");
	NT_CLIENT_INFO("Running the app");
	app->Run();
	delete app;
	return 0;
}
#endif
