#include "dgepch.h"
#include "BaseGame.h"

#include "Engine/Log.h"

#include "Engine/Renderer/Renderer.h"

#include "Engine/Input.h"

#include <GLFW/glfw3.h>

namespace DiloxGE
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	BaseGame* BaseGame::s_Instance = nullptr;

	BaseGame::BaseGame()
	{
		DGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create()); //Aca podes pasarle los valores que quieras a la ventana, creando un WindowProps
		m_Window->SetEventCallback(BIND_EVENT_FN(BaseGame::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	BaseGame::~BaseGame() { }

	void BaseGame::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				// Update all layers
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
			
			m_ImGuiLayer->Begin();

			// Execute all OnGuiRender
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

	bool BaseGame::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
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
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(BaseGame::OnWindowResize));

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