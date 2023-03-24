#include "dgepch.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace DiloxGE
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)), m_ViewMatrix(1.0f)
	{
		DGE_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		DGE_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		DGE_PROFILE_FUNCTION();

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}