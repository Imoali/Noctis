#include <Noctis.h>

class Sandbox : public Noctis::Application {
public:
	Sandbox(){
	}
	~Sandbox(){
	}
};

Noctis::Application* Noctis::CreateApplication() {
	return new Sandbox();
}