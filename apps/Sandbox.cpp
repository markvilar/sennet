#include <Sennet/Sennet.hpp>

#include <imgui.h>

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
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection 
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

		m_Shader.reset(new Sennet::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection 
					* vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Sennet::Shader(blueShaderVertexSrc, 
			blueShaderFragmentSrc));

	}

	void OnUpdate() override
	{
		if (Sennet::Input::IsKeyPressed(SN_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed;
		}
		else if (Sennet::Input::IsKeyPressed(SN_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed;
		}

		if (Sennet::Input::IsKeyPressed(SN_KEY_W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed;
		}
		else if (Sennet::Input::IsKeyPressed(SN_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed;
		}

		if (Sennet::Input::IsKeyPressed(SN_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}
		else if (Sennet::Input::IsKeyPressed(SN_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}

		Sennet::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Sennet::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Sennet::Renderer::BeginScene(m_Camera);

		Sennet::Renderer::Submit(m_BlueShader, m_SquareVa);
		Sennet::Renderer::Submit(m_Shader, m_TriangleVa);

		Sennet::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Sennet::Event& event) override
	{
	}

private:
	Sennet::Ref<Sennet::Shader> m_Shader;
	Sennet::Ref<Sennet::VertexArray> m_TriangleVa;

	Sennet::Ref<Sennet::Shader> m_BlueShader;
	Sennet::Ref<Sennet::VertexArray> m_SquareVa;

	Sennet::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraTranslationSpeed = 0.1f;
	float m_CameraRotationSpeed = 2.0f;
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
