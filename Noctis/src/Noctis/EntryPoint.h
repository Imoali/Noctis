#pragma once

#ifdef NT_PLATFORM_WINDOWS
extern Noctis::Application* Noctis::CreateApplication();
int main(int argc, char** argv) {
	Noctis::Log::Init();
	NT_CORE_WARN("WARNING!");
	int a = 10;
	NT_CLIENT_INFO("Hello! {0}", a);
	auto app = Noctis::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif
