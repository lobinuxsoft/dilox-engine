#include "BaseGame.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace DiloxGE
{
	BaseGame::BaseGame()
	{
	}

	BaseGame::~BaseGame()
	{
	}

	void BaseGame::Run()
	{
		WindowResizeEvent e(1920, 1080);
		if (e.IsInCategory(EventCategoryApplication))
		{
			DGE_TRACE(e);
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			DGE_TRACE(e);
		}

		while (true);
	}
}