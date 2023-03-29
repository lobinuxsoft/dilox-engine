#pragma once

#include "DiloxGE.h"

class ExampleLayer : public DiloxGE::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DiloxGE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DiloxGE::Event& e) override;
private:
	DiloxGE::ShaderLibrary m_ShaderLibrary;
	DiloxGE::Ref<DiloxGE::Shader> m_Shader;
	DiloxGE::Ref<DiloxGE::VertexArray> m_VertexArray;

	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;

	DiloxGE::Ref<DiloxGE::Texture2D> m_Texture, m_ChernoLogoTexture;

	DiloxGE::PerspectiveCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
