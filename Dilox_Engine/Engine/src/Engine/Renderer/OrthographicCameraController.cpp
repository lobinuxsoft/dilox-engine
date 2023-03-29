#include "dgepch.h"
#include "Engine/Renderer/OrthographicCameraController.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Keycodes.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;

namespace DiloxGE
{
	PerspectiveCameraController::PerspectiveCameraController()
	{
		m_ForwardDirection = glm::vec3(0, 0, -1);
		m_CameraPosition = glm::vec3(0, 0, 6);
		m_Yaw = -90.0f;
		m_CameraTranslationSpeed = 2.0f;
		m_CameraRotationSpeed = 2.0f;
		firstPersonCamera = true;
	}

	PerspectiveCameraController::PerspectiveCameraController(glm::vec3 targetPosition)
	{
		m_ForwardDirection = glm::vec3(0, 0, -1);
		m_CameraPosition = glm::vec3(0, 0, 6);
		m_Yaw = -90.0f;
		m_CameraTranslationSpeed = 2.0f;
		m_CameraRotationSpeed = 2.0f;
		firstPersonCamera = true;

		this->targetPosition = targetPosition;
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		DGE_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(DGE_KEY_M))
		{
			firstPersonCamera = !firstPersonCamera;
		}
		
		m_Camera.m_ForwardDirection = m_ForwardDirection;

		if (firstPersonCamera)
		{
			glm::vec2 mousePos = { Input::GetMousePosition().first, Input::GetMousePosition().second };
			glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.002f;
			m_LastMousePosition = mousePos;

			//IZQUIERDA
			if (Input::IsKeyPressed(DGE_KEY_A))
			{
				m_CameraPosition -= glm::normalize(glm::cross(m_ForwardDirection, cameraUp)) * m_CameraTranslationSpeed;
			}
			//DERECHA
			else if (Input::IsKeyPressed(DGE_KEY_D))
			{
				m_CameraPosition += glm::normalize(glm::cross(m_ForwardDirection, cameraUp)) * m_CameraTranslationSpeed;
			}
			//FORWARD
			if (Input::IsKeyPressed(DGE_KEY_Q))
			{
				m_CameraPosition += m_CameraTranslationSpeed * m_ForwardDirection;
			}
			//BACKWARD
			else if (Input::IsKeyPressed(DGE_KEY_E))
			{
				m_CameraPosition -= m_CameraTranslationSpeed * m_ForwardDirection;
			}
			//ABAJO
			if (Input::IsKeyPressed(DGE_KEY_S))
			{
				m_CameraPosition -= cameraUp * m_CameraTranslationSpeed;
			}
			//ARRIBA
			else if (Input::IsKeyPressed(DGE_KEY_W))
			{
				m_CameraPosition += cameraUp * m_CameraTranslationSpeed;
			}

			RotateCamera();

			m_Camera.SetPosition(m_CameraPosition);
		}
		else
		{
			m_Camera.SetPosition(targetPosition, true);
		}
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		DGE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(DGE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(DGE_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		DGE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f); //Impide que la camara tenga zoom negativo
		m_Camera.SetProjection();

		return false;
	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		DGE_PROFILE_FUNCTION();

		m_Camera.SetProjection();
		return false;
	}

	void PerspectiveCameraController::RotateCamera()
	{
		float xoffset = 0, yoffset = 0;

		if (Input::IsKeyPressed(DGE_KEY_RIGHT))
		{
			m_Yaw += m_CameraRotationSpeed;
		}
		else if (Input::IsKeyPressed(DGE_KEY_LEFT))
		{
			m_Yaw -= m_CameraRotationSpeed;
		}
		else if (Input::IsKeyPressed(DGE_KEY_UP))
		{
			m_Pitch += m_CameraRotationSpeed;
		}
		else if (Input::IsKeyPressed(DGE_KEY_DOWN))
		{
			m_Pitch -= m_CameraRotationSpeed;
		}

		xoffset *= 0.02f;
		yoffset *= 0.02f;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		// update Front, Right and Up Vectors using the updated Euler angles
		UpdateCameraVectors();
	}

	void PerspectiveCameraController::UpdateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_ForwardDirection = glm::normalize(front);
		// also re-calculate the Right and Up vector
		rightDirection = glm::normalize(glm::cross(m_ForwardDirection, cameraUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		cameraUp = glm::normalize(glm::cross(rightDirection, m_ForwardDirection));
	}
}