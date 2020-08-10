#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <Sennet/Sennet.hpp>

// Temporary.
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

int Sennet::main(int argc, char** argv)
{
	Sennet::Log::Init();

	//auto app = Sennet::CreateApplication();
	//app->Run();
	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}
