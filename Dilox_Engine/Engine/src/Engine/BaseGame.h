#pragma once

#include "Core.h"
#include "Window.h"
#include <Engine/LayerStack.h>
#include "Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"

namespace DiloxGE
{
	class DGE_API BaseGame
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		static BaseGame* s_Instance;

	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static BaseGame& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }
	};

	// To be defined in client
	BaseGame* CreateBaseGame();
}