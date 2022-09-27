#include "dgepch.h"
#include "BaseGame.h"

#include "Engine/Log.h"
#include "Engine/Input.h"

#include "Tools/Renderer2D.h"

#include <glad/glad.h>
#include <Tools/Triangle.h>

namespace DiloxGE
{
	float squareVertices[] =
	{
			-0.5f, -0.5f, 0.0f, //0
			0.5f, -0.5f, 0.0f, //1
			0.5f,  0.5f, 0.0f, //2
			-0.5f,  0.5f, 0.0f  //3
	};

	float triangleVertices[] =
	{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
	};


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	BaseGame* BaseGame::s_Instance = nullptr;

	BaseGame::BaseGame()
	{
		renderer2D = new Renderer2D();

		DGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create()); //Aca podes pasarle los valores que quieras a la ventana, creando un WindowProps
		m_Window->SetEventCallback(BIND_EVENT_FN(BaseGame::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// El proceso de dibujar un triangulo
		Triangle* triangle = new Triangle(renderer2D, squareVertices, true);
	}

	BaseGame::~BaseGame()
	{

	}

	void BaseGame::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			renderer2D->DrawBuffer();
			

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

			Update();
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