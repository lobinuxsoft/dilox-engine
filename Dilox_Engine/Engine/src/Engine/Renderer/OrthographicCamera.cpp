#include "dgepch.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace DiloxGE
{
	PerspectiveCamera::PerspectiveCamera()
		: m_ProjectionMatrix(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)), m_ViewMatrix(1.0f)
	{
		DGE_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection()
	{
		DGE_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		DGE_PROFILE_FUNCTION();

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix(glm::vec3 m_TargetPosition)
	{
		DGE_PROFILE_FUNCTION();
		float m_Distance = 50.0f;

		// Set the camera position behind the object
		glm::vec3 cameraPosition = m_TargetPosition - m_Distance * m_ForwardDirection;

		m_ViewMatrix = glm::lookAt(cameraPosition, m_TargetPosition, glm::vec3(0, 1, 0));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}