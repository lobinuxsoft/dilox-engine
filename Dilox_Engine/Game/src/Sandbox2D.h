#pragma once

#include "DiloxGE.h"

struct Player
{
	glm::vec4 color = { 0.2f,0.3f,0.8f,1.0f };
	float rotation = 0;
	glm::vec2 position = { 0.0f,0.0f };
	glm::vec2 scale = { 1.0f,1.0f };
};

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

	Player player1;
	Player player2;

	// Temp
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;
	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;

	DiloxGE::Ref<DiloxGE::Texture2D> m_CheckerboardTexture;
	DiloxGE::Ref<DiloxGE::Texture2D> m_SpriteSheet;
	//DiloxGE::Ref<DiloxGE::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> anim;

	float animTime = 0.0f;
	float animDuration = 3.0f;
	float animSpeed = 1.0f;
};