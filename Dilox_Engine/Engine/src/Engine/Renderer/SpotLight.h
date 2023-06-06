#pragma once
#include <glm/glm.hpp>
#include <Engine/Renderer/Shader.h>

namespace DiloxGE
{
	class DGE_API SpotLight
	{
	private:

		static int s_spotLightCount; // Contador de luces puntuales
		int m_index; // Índice de la luz puntual

		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
		float cutoff;
		float outerCutoff;

	public:

		SpotLight();
		~SpotLight();

		SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
			const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
			float constant, float linear, float quadratic, float cutoff, float outerCutoff);

		void setPosition(const glm::vec3& position);
		void setDirection(const glm::vec3& direction);
		void setColor(const glm::vec3& color);

		void setAmbient(const glm::vec3& ambient);
		void setDiffuse(const glm::vec3& diffuse);
		void setSpecular(const glm::vec3& specular);
		void setAttenuation(float constant, float linear, float quadratic);
		void setCutoff(float cutoff);
		void setOuterCutoff(float outerCutoff);

		glm::vec3 getPosition();
		glm::vec3 getDirection();
		glm::vec3 getColor();
		float getCutoff();
		float getOuterCutoff();

		void setUniforms(Shader* shader);
	};
}

