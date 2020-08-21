#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <Sennet/Sennet.hpp>

// Temporary.
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

#include "Sandbox2D.hpp"


class ExampleLayer : public Sennet::Layer
{
public:
	ExampleLayer()
		: Layer("example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_TriangleVa = Sennet::VertexArray::Create();

		float triangleVertices[3 * 7] = 
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Sennet::Ref<Sennet::VertexBuffer> triangleVb(
			Sennet::VertexBuffer::Create(triangleVertices, 
			sizeof(triangleVertices)));
		triangleVb->SetLayout({
			{ Sennet::ShaderDataType::Float3, "a_Position" },
			{ Sennet::ShaderDataType::Float4, "a_Color" }
		});

		m_TriangleVa->AddVertexBuffer(triangleVb);

		uint32_t triangleIndices[3] = { 0, 1, 2 };

		Sennet::Ref<Sennet::IndexBuffer> triangleIb(
			Sennet::IndexBuffer::Create(triangleIndices, 
			sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVa->SetIndexBuffer(triangleIb);

		// Square.
		m_SquareVa = Sennet::VertexArray::Create();

		float squareVertices[4 * 5] = 
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		
		Sennet::Ref<Sennet::VertexBuffer> squareVb(
			Sennet::VertexBuffer::Create(squareVertices,
			sizeof(squareVertices)));

		squareVb->SetLayout({
			{ Sennet::ShaderDataType::Float3, "a_Position" },
			{ Sennet::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVa->AddVertexBuffer(squareVb);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		Sennet::Ref<Sennet::IndexBuffer> squareIb(
			Sennet::IndexBuffer::Create(squareIndices,
			sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVa->SetIndexBuffer(squareIb);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform
					 * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Sennet::Shader::Create("VertexPosColor", 
			vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform
					* vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader = Sennet::Shader::Create("FlatColor",
			flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load(
			"../../assets/shaders/Texture.glsl");
		
		Sennet::Image image(std::vector<unsigned char>(1920*1080*4, 5),
			1920, 1080, 4);

		m_ImageTexture = Sennet::Texture2D::Create(image);
		
		//m_CheckerboardTexture = Sennet::Texture2D::Create(
			//"../../assets/textures/checkerboard.png");

		m_CartographTexture = Sennet::Texture2D::Create(
			"../../assets/textures/cartographer.png");

		std::dynamic_pointer_cast<Sennet::OpenGLShader>(
			textureShader)->Bind();
			

		std::dynamic_pointer_cast<Sennet::OpenGLShader>(
			textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Sennet::Timestep ts) override
	{
		// Update.
		m_CameraController.OnUpdate(ts);

		// Renderer submittion.
		Sennet::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Sennet::RenderCommand::Clear();

		Sennet::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Sennet::OpenGLShader>(
			m_FlatColorShader)->Bind();

		std::dynamic_pointer_cast<Sennet::OpenGLShader>(
			m_FlatColorShader)->UploadUniformFloat3("u_Color",
			m_SquareColor);

		// Square grid.
		for (int j = 0; j < 20; j++)
		{
			for (int i = 0; i < 20; i++)
			{
				glm::vec3 position(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(
					glm::mat4(1.0f), position) * scale;

				Sennet::Renderer::Submit(m_FlatColorShader, 
					m_SquareVa, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		// Square.
		m_ImageTexture->Bind();
		Sennet::Renderer::Submit(textureShader, m_SquareVa, 
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_CartographTexture->Bind();
		Sennet::Renderer::Submit(textureShader, m_SquareVa, 
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle.
		//Sennet::Renderer::Submit(m_Shader, m_TriangleVa);

		Sennet::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SameLine();
		Sennet::ImGuiHelpMarker("Click and drag the square to adjust "
			"the respective color component.");
		ImGui::End();
	}

	void OnEvent(Sennet::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Sennet::ShaderLibrary m_ShaderLibrary;
	Sennet::Ref<Sennet::Shader> m_Shader;
	Sennet::Ref<Sennet::VertexArray> m_TriangleVa;

	Sennet::Ref<Sennet::Shader> m_FlatColorShader;
	Sennet::Ref<Sennet::VertexArray> m_SquareVa;

	Sennet::Ref<Sennet::Texture2D> m_ImageTexture;
	Sennet::Ref<Sennet::Texture2D> m_CartographTexture;

	Sennet::OrthographicCameraController m_CameraController;
		
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Sennet::Application
{
public:
	Sandbox(bool verbose)
		: Application(verbose)
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Sennet::Application* Sennet::CreateApplication()
{
	bool verbose = false;
	return new Sandbox(verbose);
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
