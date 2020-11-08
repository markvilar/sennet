#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <Sennet/Sennet.hpp>

// Temporary.
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

#include "Sandbox2D.hpp"

class Sandbox : public Sennet::Application
{
public:
	Sandbox()
		: Application()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Sennet::Application* Sennet::CreateApplication()
{
	return new Sandbox();
}


int Sennet::main(int argc, char** argv)
{
	Sennet::Log::Init();

	SN_PROFILE_BEGIN_SESSION("Startup", "SennetProfile-Startup.json");
	auto app = Sennet::CreateApplication();
	SN_PROFILE_END_SESSION();

	SN_PROFILE_BEGIN_SESSION("Runtime", "SennetProfile-Runtime.json");
	app->Run();
	SN_PROFILE_END_SESSION();

	SN_PROFILE_BEGIN_SESSION("Shutdown", "SennetProfile-Shutdown.json");
	delete app;
	SN_PROFILE_END_SESSION();

	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}
