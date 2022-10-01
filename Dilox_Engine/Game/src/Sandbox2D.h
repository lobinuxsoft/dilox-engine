#pragma once

#include "DiloxGE.h"

class Sandbox2D : public DiloxGE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DiloxGE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DiloxGE::Event& e) override;

private:
	DiloxGE::OrtographicCameraController m_CameraController;

	// Temp
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;
	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };
};