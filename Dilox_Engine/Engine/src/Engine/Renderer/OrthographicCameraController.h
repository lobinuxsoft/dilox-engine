#pragma once

#include <Engine/Renderer/OrthographicCamera.h>
#include "Engine/Core/Timestep.h"

#include "Engine/Events/ApplicationEvent.h" //Para resizear la ventana
#include "Engine/Events/MouseEvent.h"       //Para zoom-in/zoom-out de la camara

namespace DiloxGE
{
	class DGE_API PerspectiveCameraController
	{
	public:
		PerspectiveCameraController();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void RotateCamera();
		void UpdateCameraVectors();

		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 direction;
		glm::vec3 rightDirection;

		float m_Pitch = 0;
		float m_Yaw = 0;

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f; //Es el valor con el que vamos a inicializar la camara ortografica 

		glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };
		glm::vec2 mousePos{ 0.0f, 0.0f };

		PerspectiveCamera m_Camera;

		bool firstPersonCamera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f,0.0f ,0.0f };
		glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 0.3f;
	};
}
