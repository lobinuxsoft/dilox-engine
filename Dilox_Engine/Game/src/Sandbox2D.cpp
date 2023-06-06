#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const float tilemapWidth = 17;
static const float tilemapHeight = 16;

static const float playerSpeed = 3;

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

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(), spotlight()
{

}

void Sandbox2D::OnAttach()
{
	DGE_PROFILE_FUNCTION();

	//m_SpriteSheet = DiloxGE::Texture2D::Create("assets/game/textures/character.png");

	m_CameraController.SetPlayerTarget(player1.position);


	SetTransforms();
}

void Sandbox2D::OnDetach()
{
	DGE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(DiloxGE::Timestep ts)
{
	DGE_PROFILE_FUNCTION();

	glm::vec3 size = { 1.0f,1.0f, 1.0f };


	glm::mat4 transform = glm::translate(glm::mat4(1.0f), player1.position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(player1.rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), size);

	CheckInput(ts);

	// Update
	m_CameraController.OnUpdate(ts, player1.position);

	// Render
	DiloxGE::Renderer2D::ResetStats();
	{
		DGE_PROFILE_SCOPE("Renderer Prep");
		DiloxGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DiloxGE::RenderCommand::Clear();
	}

	DGE_PROFILE_SCOPE("Renderer Draw");
	DiloxGE::Renderer2D::BeginScene(m_CameraController.GetCamera(), transform);

	DiloxGE::Renderer2D::DrawCube(player1.position, size, 1.0f, player1.color);

	//DiloxGE::Renderer2D::DrawQuad(player1.position, player1.scale, player1.animations[animIndex]->Animate(ts), 1.0f, player1.color);

	DiloxGE::Renderer2D::EndScene();
}

void Sandbox2D::SetTransforms()
{
	player3.position = { -2.0f,0.0f,0.0f };
	player3.scale = { 1.0f,1.0f };
	player3.color = { 1.0f,1.0f,1.0f,1.0f };
	player3.rotation = 0;

	player1.position = { 0.0f,0.0f,0.0f };
	player1.scale = { 1.0f,1.0f };
	player1.color = { 1.0f,1.0f,1.0f,1.0f };
	player1.rotation = 0;

	player2.position = { 1.0f,1.0f,0.0f };
	player2.scale = { 1.0f,1.0f };
	player2.color = { 1.0f,1.0f,1.0f,1.0f };
	player2.rotation = 0;
}

void Sandbox2D::CheckInput(DiloxGE::Timestep ts)
{
	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_LEFT))
	{
		player1.position.x -= playerSpeed * ts;
	}

	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_RIGHT))
	{
		player1.position.x += playerSpeed * ts;
	}

	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_UP))
	{
		player1.position.y += playerSpeed * ts;
	}

	if (DiloxGE::Input::IsKeyPressed(DGE_KEY_DOWN))
	{
		player1.position.y -= playerSpeed * ts;
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

	ImGui::End();
}

void Sandbox2D::OnEvent(DiloxGE::Event& e)
{
	m_CameraController.OnEvent(e);
}

