#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace DiloxGE
{
	class DGE_API BaseGame
	{
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();
	};

	// To be defined in client
	BaseGame* CreateBaseGame();
}