#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const int s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WGGWWWWWWWGGGGGGGGGGGGGW"
"WGGGGGWWGGGGGGGGGGGGGGGW"
"WGGGGGGGGGGGGGGGGGGGGGGW"
"WGGGGGGGGGGWWWWWGGGGGGGW"
"WGGGGGGGGGGGGGGGGGGGGGGW"
"WGGGGGGGGGGGGGGGGGGGGGGW"
"WGGWWGGGGGGGGGGGGGGGGGGW"
"WGGGGWWWWWWWGGGGGWWWGGGW"
"WGGGGGGGGGGGGGGWWWWGGGGW"
"WGGGWWWWGGGGGGGGGGGGGGGW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) { }

void Sandbox2D::OnAttach()
{
	DGE_PROFILE_FUNCTION();

	m_SpriteSheet = DiloxGE::Texture2D::Create("assets/game/textures/character.png");

	m_Atlas = DiloxGE::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_RoyAtlas = DiloxGE::Texture2D::Create("assets/game/textures/Roy.png");

	m_MapWidth = s_MapWidth;

	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	m_GrassTile = DiloxGE::SubTexture2D::CreateFromCoords(m_Atlas, { 1,11 }, { 128,128 }, { 1,1 });
	m_WaterTile = DiloxGE::SubTexture2D::CreateFromCoords(m_Atlas, { 11,11 }, { 128,128 }, { 1,1 });

	s_TextureMap['G'] = m_GrassTile;
	s_TextureMap['W'] = m_WaterTile;

	SetTransforms();

	CreateAnimations();
}

void Sandbox2D::OnDetach()
{
	DGE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(DiloxGE::Timestep ts)
{
	DGE_PROFILE_FUNCTION();

	CheckInput(ts);

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	DiloxGE::Renderer2D::ResetStats();
	{
		DGE_PROFILE_SCOPE("Renderer Prep");
		DiloxGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DiloxGE::RenderCommand::Clear();
	}

	DGE_PROFILE_SCOPE("Renderer Draw");
	DiloxGE::Renderer2D::BeginScene(m_CameraController.GetCamera());

	DiloxGE::Renderer2D::DrawQuad(player1.position, player1.scale, player1.animations[animIndex]->Animate(ts), 1.0f, player1.color);

	for (int y = 0; y < m_MapHeight; y++)
	{
		for (int x = 0; x < m_MapWidth; x++)
		{
			auxTile[y][x].tileType = s_MapTiles[x + y * m_MapWidth];
			//char tileType = s_MapTiles[x + y * m_MapWidth];

			if (s_TextureMap.find(auxTile[y][x].tileType) != s_TextureMap.end())
			{
				tileTexture = s_TextureMap[auxTile[y][x].tileType];
			}
			else
			{
				tileTexture = m_GrassTile;
			}

			auxTile[y][x].position = { m_MapWidth - x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f };

			DiloxGE::Renderer2D::DrawQuad(auxTile[y][x].position, { 1,1 }, tileTexture, 1.0f, player3.color);
		}
	}

	for (int y = 0; y < m_MapHeight; y++)
	{
		for (int x = 0; x < m_MapWidth; x++)
		{
			CheckCollision(player1, auxTile[y][x]);
		}
	}

	//CheckCollision(player1, player2);

	DiloxGE::Renderer2D::EndScene();
}

bool Sandbox2D::CheckCollision(Entity& player1, Entity& player2)
{
	if (player1.position.x < player2.position.x + player2.scale.x &&
		player1.position.x + player1.scale.x > player2.position.x &&
		player1.position.y < player2.position.y + player2.scale.y &&
		player1.position.y + player1.scale.y > player2.position.y)
	{
		glm::vec2 dir = player2.position - player1.position;
		dir = glm::normalize(dir);
		float dist = glm::distance(player1.position, player2.position);

		player1.position -= dir * (dist * 0.025f);
		return true;
	}
	else
	{
		return false;
	}
}

bool Sandbox2D::CheckCollision(Entity& player1, Tile& tile)
{
	if (player1.position.x < tile.position.x + tile.scale.x &&
		player1.position.x + player1.scale.x > tile.position.x &&
		player1.position.y < tile.position.y + tile.scale.y &&
		player1.position.y + player1.scale.y > tile.position.y)
	{
		if (tile.tileType == 'W')
		{
			glm::vec2 dir = tile.position - player1.position;
			dir = glm::normalize(dir);
			float dist = glm::distance(player1.position, tile.position);

			player1.position -= dir * (dist * 0.025f);

			std::cout << "colisiono";
			return true;
		}
	}
	else
	{
		return false;
	}
}


void Sandbox2D::CreateAnimations()
{
	animRoy.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_RoyAtlas, { 0, 0 }, { 64, 64 }, { 1, 1 }));
	animRoy.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_RoyAtlas, { 1, 0 }, { 64, 64 }, { 1, 1 }));
	animRoy.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_RoyAtlas, { 2, 0 }, { 64, 64 }, { 1, 1 }));
	animRoy.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_RoyAtlas, { 3, 0 }, { 64, 64 }, { 1, 1 }));
	animRoy.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_RoyAtlas, { 4, 0 }, { 64, 64 }, { 1, 1 }));
	animRoy.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_RoyAtlas, { 5, 0 }, { 64, 64 }, { 1, 1 }));

	player3.animations.push_back(DiloxGE::Animation::Create(animRoy, 16));

	animDown.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 3 }, { 64, 64 }, { 1, 1 }));
	animDown.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 3 }, { 64, 64 }, { 1, 1 }));
	animDown.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 3 }, { 64, 64 }, { 1, 1 }));
	animDown.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 3 }, { 64, 64 }, { 1, 1 }));

	animUp.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 0 }, { 64, 64 }, { 1, 1 }));
	animUp.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 0 }, { 64, 64 }, { 1, 1 }));
	animUp.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 0 }, { 64, 64 }, { 1, 1 }));
	animUp.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 0 }, { 64, 64 }, { 1, 1 }));

	animLeft.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 2 }, { 64, 64 }, { 1, 1 }));
	animLeft.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 2 }, { 64, 64 }, { 1, 1 }));
	animLeft.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 2 }, { 64, 64 }, { 1, 1 }));
	animLeft.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 2 }, { 64, 64 }, { 1, 1 }));

	animRight.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 1 }, { 64, 64 }, { 1, 1 }));
	animRight.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 1 }, { 64, 64 }, { 1, 1 }));
	animRight.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 64, 64 }, { 1, 1 }));
	animRight.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 1 }, { 64, 64 }, { 1, 1 }));

	player1.animations.push_back(DiloxGE::Animation::Create(animDown, 16));
	player1.animations.push_back(DiloxGE::Animation::Create(animUp, 16));
	player1.animations.push_back(DiloxGE::Animation::Create(animLeft, 16));
	player1.animations.push_back(DiloxGE::Animation::Create(animRight, 16));
}

void Sandbox2D::SetTransforms()
{
	player3.position = { -2.0f,0.0f };
	player3.scale = { 1.0f,1.0f };
	player3.color = { 1.0f,1.0f,1.0f,1.0f };
	player3.rotation = 0;

	player1.position = { 0.0f,0.0f };
	player1.scale = { 1.0f,1.0f };
	player1.color = { 1.0f,1.0f,1.0f,1.0f };
	player1.rotation = 0;

	player2.position = { 1.0f,1.0f };
	player2.scale = { 1.0f,1.0f };
	player2.color = { 1.0f,1.0f,1.0f,1.0f };
	player2.rotation = 0;
}

void Sandbox2D::CheckInput(DiloxGE::Timestep ts)
{
	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_LEFT))
	{
		animIndex = 2;
		player1.position.x -= ts;
	}

	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_RIGHT))
	{
		animIndex = 3;
		player1.position.x += ts;
	}

	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_UP))
	{
		animIndex = 1;
		player1.position.y += ts;
	}

	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_DOWN))
	{
		animIndex = 0;
		player1.position.y -= ts;
	}
}

void Sandbox2D::OnImGuiRender()
{
	DGE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = DiloxGE::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4(
		"Player1 Color",
		glm::value_ptr(player1.color),
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar
	);

	ImGui::DragFloat2("Translation", glm::value_ptr(player1.position), 0.1f);

	ImGui::DragFloat2("Scale", glm::value_ptr(player1.scale), 0.1f);

	ImGui::DragFloat2("Translation2", glm::value_ptr(player2.position), 0.1f);

	ImGui::DragFloat2("Scale2", glm::value_ptr(player2.scale), 0.1f);

	ImGui::DragFloat("Animation Duration Time", &animSpeed, 0.1f);


	ImGui::End();
}

void Sandbox2D::OnEvent(DiloxGE::Event& e)
{
	m_CameraController.OnEvent(e);
}

