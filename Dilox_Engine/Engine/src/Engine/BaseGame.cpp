#include "dgepch.h"
#include "BaseGame.h"

#include "Engine/Log.h"

#include "Engine/Renderer/Renderer.h"

#include "Engine/Input.h"

namespace DiloxGE
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	BaseGame* BaseGame::s_Instance = nullptr;

	BaseGame::BaseGame()
	{
		DGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create()); //Aca podes pasarle los valores que quieras a la ventana, creando un WindowProps
		m_Window->SetEventCallback(BIND_EVENT_FN(BaseGame::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	BaseGame::~BaseGame() { }

	void BaseGame::Run()
	{
		while (m_Running)
		{
			// Update all layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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