#include "dgepch.h"
#include "BaseGame.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

#include <glfw3.h>

namespace DiloxGE
{
	BaseGame::BaseGame()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	BaseGame::~BaseGame()
	{
	}

	void BaseGame::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}