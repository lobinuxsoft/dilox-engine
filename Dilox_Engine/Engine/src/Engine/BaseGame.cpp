#include "dgepch.h"
#include "BaseGame.h"

#include "Engine/Log.h"
#include "Engine/Input.h"

#include <glad/glad.h>

namespace DiloxGE
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	BaseGame* BaseGame::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case DiloxGE::ShaderDataType::Float:	return GL_FLOAT;
			case DiloxGE::ShaderDataType::Float2:	return GL_FLOAT;
			case DiloxGE::ShaderDataType::Float3:	return GL_FLOAT;
			case DiloxGE::ShaderDataType::Float4:	return GL_FLOAT;
			case DiloxGE::ShaderDataType::Mat3:		return GL_FLOAT;
			case DiloxGE::ShaderDataType::Mat4:		return GL_FLOAT;
			case DiloxGE::ShaderDataType::Int:		return GL_INT;
			case DiloxGE::ShaderDataType::Int2:		return GL_INT;
			case DiloxGE::ShaderDataType::Int3:		return GL_INT;
			case DiloxGE::ShaderDataType::Int4:		return GL_INT;
			case DiloxGE::ShaderDataType::Bool:		return GL_BOOL;
		}

		DGE_CORE_ASSERT(false, "Unknoen ShaderDataType!");
		return 0;
	}

	BaseGame::BaseGame()
	{
		DGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create()); //Aca podes pasarle los valores que quieras a la ventana, creando un WindowProps
		m_Window->SetEventCallback(BIND_EVENT_FN(BaseGame::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// El proceso de dibujar un triangulo
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;

		const auto& layaout = m_VertexBuffer->GetLayout();

		for (const auto& element : layaout)
		{
			glEnableVertexAttribArray(index);

			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layaout.GetStride(),
				(const void*)element.Offset
			);

			index++;
		}


		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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
	}

	BaseGame::~BaseGame() { }

	void BaseGame::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			auto [x, y] = Input::GetMousePosition();
			//DGE_CORE_TRACE("{0}", "{1}", x, y);

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool BaseGame::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void BaseGame::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void BaseGame::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void BaseGame::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(BaseGame::OnWindowClose));

		//Esta linea mostraria todos los eventos automaticos (posicion del mouse, 
		//DGE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			if (e.Handled)	
			{
				break;
			}
		}
	}
}