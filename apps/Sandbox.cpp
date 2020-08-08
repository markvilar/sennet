#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <Sennet/Sennet.hpp>

// Temporary.
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

class ExampleLayer : public Sennet::Layer
{
public:
	ExampleLayer()
		: Layer("example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f), m_CameraRotation(0.0f)
	{
		m_TriangleVa.reset(Sennet::VertexArray::Create());

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

		m_SquareVa.reset(Sennet::VertexArray::Create());

		float squareVertices[4 * 3] = 
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		
		Sennet::Ref<Sennet::VertexBuffer> squareVb(
			Sennet::VertexBuffer::Create(squareVertices,
			sizeof(squareVertices)));

		squareVb->SetLayout({
			{ Sennet::ShaderDataType::Float3, "a_Position" },
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

		m_Shader.reset(Sennet::Shader::Create(vertexSrc, fragmentSrc));

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

		m_FlatColorShader.reset(Sennet::Shader::Create(
			flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(Sennet::Timestep ts) override
	{
		// Camera x position.
		if (Sennet::Input::IsKeyPressed(SN_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Sennet::Input::IsKeyPressed(SN_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		// Camera y position.
		if (Sennet::Input::IsKeyPressed(SN_KEY_W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Sennet::Input::IsKeyPressed(SN_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		// Camera rotation.
		if (Sennet::Input::IsKeyPressed(SN_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (Sennet::Input::IsKeyPressed(SN_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		Sennet::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Sennet::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Sennet::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Sennet::OpenGLShader>(
			m_FlatColorShader)->Bind();

		std::dynamic_pointer_cast<Sennet::OpenGLShader>(
			m_FlatColorShader)->UploadUniformFloat3("u_Color",
			m_SquareColor);

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
				
		Sennet::Renderer::Submit(m_Shader, m_TriangleVa);

		Sennet::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Sennet::Event& event) override
	{
	}

private:
	Sennet::Ref<Sennet::Shader> m_Shader;
	Sennet::Ref<Sennet::VertexArray> m_TriangleVa;

	Sennet::Ref<Sennet::Shader> m_FlatColorShader;
	Sennet::Ref<Sennet::VertexArray> m_SquareVa;

	Sennet::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraTranslationSpeed = 1.5f;
	float m_CameraRotationSpeed = 70.0f;
	
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Sennet::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
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
