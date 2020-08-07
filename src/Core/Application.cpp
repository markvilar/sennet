#include <Sennet/pch.hpp>
#include <Sennet/Core/Application.hpp>

#include <glad/glad.h>

#include <Sennet/Core/Log.hpp>
#include <Sennet/Core/Input.hpp>

namespace Sennet
{

Application* Application::s_Instance = nullptr;

Application::Application()
{
	SN_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = Window::Create();
	m_Window->SetEventCallback(SN_BIND_EVENT_FN(Application::OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);

	m_TriangleVa.reset(VertexArray::Create());

	float triangleVertices[3 * 7] = 
	{
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Ref<VertexBuffer> triangleVb(VertexBuffer::Create(triangleVertices, 
		sizeof(triangleVertices)));
	triangleVb->SetLayout({
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" }
	});

	m_TriangleVa->AddVertexBuffer(triangleVb);

	uint32_t triangleIndices[3] = { 0, 1, 2 };

	Ref<IndexBuffer> triangleIb(IndexBuffer::Create(triangleIndices, 
		sizeof(triangleIndices) / sizeof(uint32_t)));
	m_TriangleVa->SetIndexBuffer(triangleIb);

	// Square.

	m_SquareVa.reset(VertexArray::Create());

	float squareVertices[4 * 3] = 
	{
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f
	};
	
	Ref<VertexBuffer> squareVb(VertexBuffer::Create(squareVertices,
		sizeof(squareVertices)));

	squareVb->SetLayout({
		{ ShaderDataType::Float3, "a_Position" },
	});
	m_SquareVa->AddVertexBuffer(squareVb);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	Ref<IndexBuffer> squareIb(IndexBuffer::Create(squareIndices, 
		sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVa->SetIndexBuffer(squareIb);

	std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec3 v_Position;
		out vec4 v_Color;
		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);	
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

	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	std::string blueShaderVertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		out vec3 v_Position;
		void main()
		{
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);	
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

	m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
}

Application::~Application()
{
}

void Application::OnEvent(Event& e)
{
	// Dispatch event.
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(
		SN_BIND_EVENT_FN(Application::OnWindowClose));

	// Propagate event through Layers.
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
		{
			break;
		}
	}
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Application::Close()
{
}

void Application::Run()
{
	while (m_Running)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//RenderCommand::SetClearColor();
		//RenderCommand::Clear();

		//Renderer::BeginScene();

		m_BlueShader->Bind();
		//Renderer::Submit(m_SquareVa);

		m_SquareVa->Bind();
		//Renderer::Submit(m_TriangleVa);

		//Renderer::EndScene();

		glDrawElements(GL_TRIANGLES, 
			m_SquareVa->GetIndexBuffer()->GetCount(),
			GL_UNSIGNED_INT, 
			nullptr);

		m_Shader->Bind();
		m_TriangleVa->Bind();
		glDrawElements(GL_TRIANGLES, 
			m_TriangleVa->GetIndexBuffer()->GetCount(), 
			GL_UNSIGNED_INT, 
			nullptr);

		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
		}
		
		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}
		m_ImGuiLayer->End();

		m_Window->OnUpdate();
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	return true;
}

};
