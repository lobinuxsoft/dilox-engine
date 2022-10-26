#pragma once
#include "Base.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/Event.h"

namespace DiloxGE
{
	class DGE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		///<summary>
		///Cuando se pushea una layer en el stack de layers
		///</summary>
		virtual void OnAttach() {}

		///<summary>
		///Lo contrario al OnAttach
		///</summary>
		virtual void OnDetach() {}

		///<summary>
		///Ocurre cada frame
		///</summary>
		virtual void OnUpdate(Timestep ts) {}

		virtual void OnImGuiRender() {}

		///<summary>
		///Cuando se envia un evento al layer, se recibe aca
		///</summary>
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; //Es solo para debug
	};
}


