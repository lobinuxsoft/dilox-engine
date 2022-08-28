#pragma once

#include "Core.h"
#include "Window.h"
#include <Engine/LayerStack.h>
#include "Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

//#include <Engine/Layer.h>

namespace DiloxGE
{
	class DGE_API BaseGame
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	};

	// To be defined in client
	BaseGame* CreateBaseGame();
}