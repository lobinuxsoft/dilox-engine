#pragma once

#include "Core.h"

namespace DiloxGE
{
	class DGE_API BaseGame
	{
	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();
	};

	// To be defined in client
	BaseGame* CreateBaseGame();
}