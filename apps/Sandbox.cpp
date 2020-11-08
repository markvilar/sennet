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
	auto app = Sennet::CreateApplication();
	app->Run();
	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}
