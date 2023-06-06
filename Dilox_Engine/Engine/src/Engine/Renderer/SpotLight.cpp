#include "dgepch.h"
#include "Engine/Renderer/SpotLight.h"
#include <Engine/Renderer/Shader.h>

namespace DiloxGE
{
	int SpotLight::s_spotLightCount = 0; // Inicializamos el contador de luces puntuales en 0

	SpotLight::SpotLight()
		: m_index(s_spotLightCount++),
		position(glm::vec3(0.0f, 5.0f, 0.0f)),
		direction(glm::vec3(0.0f, -1.0f, 0.0f)),
		color(glm::vec3(1.0f)),
		ambient(glm::vec3(0.2f)),
		diffuse(glm::vec3(0.5f)),
		specular(glm::vec3(0.8f)),
		constant(1.0f),
		linear(0.09f),
		quadratic(0.032f),
		cutoff(glm::cos(glm::radians(45.0f))),
		outerCutoff(glm::cos(glm::radians(70.0f)))
	{
		DGE_PROFILE_FUNCTION();
	}

	SpotLight::~SpotLight()
	{
		DGE_PROFILE_FUNCTION();
	}

	SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
		const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic, float cutoff, float outerCutoff)
		: m_index(s_spotLightCount++),
		position(position),
		direction(direction),
		color(color),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		constant(constant),
		linear(linear),
		quadratic(quadratic),
		cutoff(cutoff),
		outerCutoff(outerCutoff)
	{
		DGE_PROFILE_FUNCTION();
	}

	void SpotLight::setPosition(const glm::vec3& position)
	{
		DGE_PROFILE_FUNCTION();
		this->position = position;
	}

	void SpotLight::setDirection(const glm::vec3& direction)
	{
		DGE_PROFILE_FUNCTION();
		this->direction = direction;
	}

	void SpotLight::setColor(const glm::vec3& color)
	{
		DGE_PROFILE_FUNCTION();
		this->color = color;
	}

	void SpotLight::setAmbient(const glm::vec3& ambient)
	{
		DGE_PROFILE_FUNCTION();
		this->ambient = ambient;
	}

	void SpotLight::setDiffuse(const glm::vec3& diffuse)
	{
		DGE_PROFILE_FUNCTION();
		this->diffuse = diffuse;
	}

	void SpotLight::setSpecular(const glm::vec3& specular)
	{
		DGE_PROFILE_FUNCTION();
		this->specular = specular;
	}

	void SpotLight::setAttenuation(float constant, float linear, float quadratic)
	{
		DGE_PROFILE_FUNCTION();
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	void SpotLight::setCutoff(float cutoff)
	{
		DGE_PROFILE_FUNCTION();
		this->cutoff = cutoff;
	}

	void SpotLight::setOuterCutoff(float outerCutoff)
	{
		DGE_PROFILE_FUNCTION();
		this->outerCutoff = outerCutoff;
	}

	glm::vec3 SpotLight::getPosition()
	{
		DGE_PROFILE_FUNCTION();
		return position;
	}

	glm::vec3 SpotLight::getDirection()
	{
		DGE_PROFILE_FUNCTION();
		return direction;
	}

	glm::vec3 SpotLight::getColor()
	{
		DGE_PROFILE_FUNCTION();
		return color;
	}

	float SpotLight::getCutoff()
	{
		DGE_PROFILE_FUNCTION();
		return cutoff;
	}

	float SpotLight::getOuterCutoff()
	{
		DGE_PROFILE_FUNCTION();
		return outerCutoff;
	}

	void SpotLight::setUniforms(Shader* shader)
	{
		DGE_PROFILE_FUNCTION();
		shader->Bind();
			  
		shader->SetFloat("numSpotLights", s_spotLightCount);
			  
		shader->SetFloat3("spotLights[" + std::to_string(m_index) + "].position",   position);
		shader->SetFloat3("spotLights[" + std::to_string(m_index) + "].direction",  direction);
		shader->SetFloat3("spotLights[" + std::to_string(m_index) + "].color",		color);
		shader->SetFloat3("spotLights[" + std::to_string(m_index) + "].ambient",	ambient);
		shader->SetFloat3("spotLights[" + std::to_string(m_index) + "].diffuse",	diffuse);
		shader->SetFloat3("spotLights[" + std::to_string(m_index) + "].specular",	specular);
			  
		shader->SetFloat("spotLights[" + std::to_string(m_index) + "].constant", constant);
		shader->SetFloat("spotLights[" + std::to_string(m_index) + "].linear", linear);
		shader->SetFloat("spotLights[" + std::to_string(m_index) + "].quadratic", quadratic);
		shader->SetFloat("spotLights[" + std::to_string(m_index) + "].cutoff", cutoff);
		shader->SetFloat("spotLights[" + std::to_string(m_index) + "].outerCutoff", outerCutoff);
			  
		shader->Unbind();
	}
}