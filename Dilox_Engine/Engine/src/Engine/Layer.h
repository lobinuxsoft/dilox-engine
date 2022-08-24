#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace DiloxGE
{
	class DGE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {} //Cuando se pushea una layer en el stack de layers
		virtual void OnDetach() {} //Lo contrario
		virtual void OnUpdate() {} //Ocurre cada frame
		virtual void OnEvent(Event& event) {} //Cuando se envia un evento al layer, se recibe aca

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; //Es solo para debug
	};
}


