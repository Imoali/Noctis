#include <Noctis.h>

class ExampleLayer : public Noctis::Layer {
public:
	ExampleLayer()
		:Layer("Example") {};

	void OnUpdate() override {
		NT_CLIENT_INFO("updated layer");
	}
	void OnEvent(Noctis::Event & e) override {
		NT_CLIENT_INFO("EVENT! {0}", e);
	}
};

class Sandbox : public Noctis::Application {
public:
	Sandbox(){
		PushLayer(new ExampleLayer());
		PushOverlay(new Noctis::ImGuiLayer());
	}
	~Sandbox(){
	}
};

Noctis::Application* Noctis::CreateApplication() {
	return new Sandbox();
}