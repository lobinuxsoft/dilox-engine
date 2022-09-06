#pragma once
#include "dgepch.h"
#include "Input.h" 

#include "GLFW/glfw3.h"
#include "Engine/BaseGame.h"

namespace DiloxGE
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override
		{
			auto window = static_cast<GLFWwindow*>(BaseGame::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, keycode);

			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

	};
}
