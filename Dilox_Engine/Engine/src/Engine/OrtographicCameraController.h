#pragma once

#include <Engine/Renderer/OrthographicCamera.h>
#include "Engine\Core\Timestep.h"

#include "Engine\Events\ApplicationEvent.h" //Para resizear la ventana
#include "Engine\Events\MouseEvent.h"       //Para zoom-in/zoom-out de la camara

namespace DiloxGE
{
	class DGE_API OrtographicCameraController
	{
	public:
		OrtographicCameraController(float aspectRatio, bool rotation = false); //aspect ratio *  2 units

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f; //Es el valor con el que vamos a inicializar la camara ortografica 

		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f,0.0f ,0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 90.0f;
	};
}
