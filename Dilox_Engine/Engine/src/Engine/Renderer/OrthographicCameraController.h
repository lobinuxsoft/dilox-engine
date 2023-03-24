#pragma once

#include <Engine/Renderer/OrthographicCamera.h>
#include "Engine/Core/Timestep.h"

#include "Engine/Events/ApplicationEvent.h" //Para resizear la ventana
#include "Engine/Events/MouseEvent.h"       //Para zoom-in/zoom-out de la camara

namespace DiloxGE
{
	class DGE_API OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false); //aspect ratio *  2 units

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void FollowCursor();
		void UpdateCameraVectors();

		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 direction;
		glm::vec3 rightDirection;

		float lastX, lastY;
		float m_Pitch = 0;
		float m_Yaw = 0;

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f; //Es el valor con el que vamos a inicializar la camara ortografica 

		glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };
		glm::vec2 mousePos{ 0.0f, 0.0f };

		OrthographicCamera m_Camera;

		bool firstMouse;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f,0.0f ,0.0f };
		glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };
		//glm::vec3 m_CameraRotation = { 0.0f,0.0f ,0.0f }; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}
