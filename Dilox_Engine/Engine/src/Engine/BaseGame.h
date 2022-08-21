#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Window.h"

namespace DiloxGE
{
	class DGE_API BaseGame
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();

		void OnEvent(Event& e);
	};

	// To be defined in client
	BaseGame* CreateBaseGame();
}