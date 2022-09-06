#pragma once

#include "Engine/Core.h"

namespace DiloxGE
{
	class DGE_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode);}
			
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0; //La implementacion del IsKeyPressed

	private:
		static Input* s_Instance;  //ES UN SINGLETON!!!
	};
}