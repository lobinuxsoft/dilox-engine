#pragma once

#include "DiloxGE.h"

struct Entity
{
	glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f };
	float rotation = 0;
	glm::vec3 position = { 0.0f,0.0f, 0.0f };
	glm::vec2 scale = { 1.0f,1.0f };
	std::vector<DiloxGE::Ref<DiloxGE::Animation>> animations;

	DiloxGE::Ref<DiloxGE::SubTexture2D> Animate(int index, float delta)
	{
		if (index >= animations.size())
			index = animations.size() - 1;

		return animations[index]->Animate(delta);
	}
};

struct Tile
{
	char tileType;
	glm::vec2 position;
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
	DiloxGE::PerspectiveCameraController m_CameraController;

	Entity player1;
	Entity player2;
	Entity player3;
	Tile auxTile[32][32];

	// Temp
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;
	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;

	//DiloxGE::Ref<DiloxGE::Texture2D> m_CheckerboardTexture;
	DiloxGE::Ref<DiloxGE::Texture2D> m_SpriteSheet;
	//DiloxGE::Ref<DiloxGE::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;
	DiloxGE::Ref<DiloxGE::Texture2D> m_Atlas;
	DiloxGE::Ref<DiloxGE::Texture2D> m_RoyAtlas;

	DiloxGE::Ref<DiloxGE::SubTexture2D> m_GrassTile;
	DiloxGE::Ref<DiloxGE::SubTexture2D> m_WaterTile;

	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animDown;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animUp;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animLeft;
	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animRight;

	std::vector<DiloxGE::Ref<DiloxGE::SubTexture2D>> animRoy;

	DiloxGE::Ref<DiloxGE::SubTexture2D> tileTexture;

	void CreateAnimations();
	void SetTransforms();
	void CheckInput(DiloxGE::Timestep ts);

	int animIndex = 0;
	float animTime = 0.0f;
	float animDuration = 3.0f;
	float animSpeed = 1.0f;

	bool firstInit = false;

	int m_MapWidth, m_MapHeight;

	std::unordered_map<char, DiloxGE::Ref<DiloxGE::SubTexture2D>> s_TextureMap;
};