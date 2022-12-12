#pragma once

#include "DiloxGE.h"

struct Player
{
	glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f };
	float rotation = 0;
	glm::vec2 position = { 0.0f,0.0f };
	glm::vec2 scale = { 1.0f,1.0f };
	std::vector<DiloxGE::Ref<DiloxGE::Animation>> animations;

	DiloxGE::Ref<DiloxGE::SubTexture2D> Animate(int index, float delta)
	{
		if (index >= animations.size())
			index = animations.size() - 1;

		return animations[index]->Animate(delta);
	}
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
	Player player3;

	// Temp
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;
	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;

	//DiloxGE::Ref<DiloxGE::Texture2D> m_CheckerboardTexture;
	DiloxGE::Ref<DiloxGE::Texture2D> m_SpriteSheet;
	//DiloxGE::Ref<DiloxGE::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;
	DiloxGE::Ref<DiloxGE::Texture2D> m_Atlas;
	DiloxGE::Ref<DiloxGE::Texture2D> m_RoyAtlas;

	DiloxGE::Ref<DiloxGE::SubTexture2D> m_TextureBarrel;

	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animDown;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animUp;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animLeft;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animRight;

	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animRoy;

	void CheckCollision(Player& player1, Player& player2);
	void CreateAnimations();
	void SetTransforms();

	int animIndex = 0;
	float animTime = 0.0f;
	float animDuration = 3.0f;
	float animSpeed = 1.0f;
};