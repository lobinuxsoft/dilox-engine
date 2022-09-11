#pragma once

#include "Engine/Layer.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"

namespace DiloxGE
{
	class DGE_API ImGuiLayer : public Layer
	{
	private:
		float m_Time = 0.0f;


	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}