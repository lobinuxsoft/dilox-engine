#pragma once

#include "Core.h"
#include "Window.h"
#include <Engine/LayerStack.h>
#include "Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/ImGui/ImGuiLayer.h"
#include "Tools/Renderer2D.h"

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

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		static BaseGame* s_Instance;
		Renderer2D* renderer2D;

	public:
		BaseGame();
		virtual ~BaseGame();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		/// <summary>
		/// Inicializa la clase
		/// </summary>
		virtual void Begin() = 0;

		/// <summary>
		/// Updatea la clase
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// Destruye la clase
		/// </summary>
		virtual void End() = 0;

		inline static BaseGame& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }
	};

	// To be defined in client
	BaseGame* CreateBaseGame();
}