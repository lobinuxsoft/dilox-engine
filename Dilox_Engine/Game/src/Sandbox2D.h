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
	DiloxGE::OrthographicCameraController m_CameraController;

	// Temp
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;
	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;

	DiloxGE::Ref<DiloxGE::Texture2D> m_CheckerboardTexture;
	DiloxGE::Ref<DiloxGE::Texture2D> m_SpriteSheet;
	DiloxGE::Ref<DiloxGE::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;


	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };
	float m_SquareRotation = 0;
	glm::vec2 m_SquarePos = { 0.0f,0.0f };
	glm::vec2 m_SquareScale = { 1.0f,1.0f };
};