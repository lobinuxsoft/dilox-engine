#pragma once
#include <glm/glm.hpp>


namespace DiloxGE
{
	class DGE_API PerspectiveCamera
	{
	public:
		PerspectiveCamera();

		void SetProjection();

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position; 
			RecalculateViewMatrix(); 
		}

		void SetPosition(const glm::vec3& m_TargetPosition, bool thirdPerson) 
		{
			//m_Position = m_TargetPosition;
			RecalculateViewMatrix(m_TargetPosition);
		}

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		glm::vec3 m_ForwardDirection = glm::vec3(0, 0, -1);

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };

		void RecalculateViewMatrix();
		void RecalculateViewMatrix(glm::vec3 m_TargetPosition);
	};

}