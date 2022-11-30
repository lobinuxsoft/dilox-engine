#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) { }

void Sandbox2D::OnAttach()
{
	DGE_PROFILE_FUNCTION();

	//m_CheckerboardTexture = DiloxGE::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = DiloxGE::Texture2D::Create("assets/game/textures/character.png");

	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 3 }, { 64, 64 }, { 1, 1 }));
	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 3 }, { 64, 64 }, { 1, 1 }));
	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 3 }, { 64, 64 }, { 1, 1 }));
	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 3 }, { 64, 64 }, { 1, 1 }));

	player1.position = { 0.0f,0.0f };
	player1.scale = { 1.0f,1.0f };
	player1.color = { 0.2f,0.3f,0.8f,1.0f };
	player1.rotation = 0;

	player2.position = { 1.0f,1.0f };
	player2.scale = { 1.0f,1.0f };
	player2.color = { 0.2f,0.3f,0.8f,1.0f };
	player2.rotation = 0;
}

void Sandbox2D::OnDetach()
{
	DGE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(DiloxGE::Timestep ts)
{
	DGE_PROFILE_FUNCTION();

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
	
	//DiloxGE::Renderer2D::DrawQuad({1,0}, {1,1}, m_TextureStairs);
	//DiloxGE::Renderer2D::DrawQuad({0,1}, {1,1}, m_TextureBarrel);
	//DiloxGE::Renderer2D::DrawQuad({0,-1}, {1.0f,1.5f}, m_TextureTree);
	
	animTime += ts * animSpeed;

	if (animTime > animDuration)
		animTime -= animDuration;


	DiloxGE::Renderer2D::DrawQuad(player1.position, player1.scale, anim[static_cast<int>((animTime / animDuration) * anim.size()) % anim.size()], 1.0f, player1.color);

	DiloxGE::Renderer2D::DrawQuad(player2.position, player2.scale, glm::vec4(1, 1, 1, 1));

	if (player1.position.x < player2.position.x + player2.scale.x &&
		player1.position.x + player1.scale.x > player2.position.x &&
		player1.position.y < player2.position.y + player2.scale.y &&
		player1.position.y + player1.scale.y > player2.position.y)
	{
		if (player1.position.x > player2.position.x)
		{
			player2.position.x -= 0.1f;
		}
		if (player1.position.x < player2.position.x)
		{
			player2.position.x += 0.1f;
		}
	}

	//DiloxGE::Renderer2D::DrawQuad({ 0,0 }, { 10,10 }, m_CheckerboardTexture);

	DiloxGE::Renderer2D::EndScene();

	/*{
		DiloxGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		DiloxGE::Renderer2D::DrawRotatedQuad(m_SquarePos, m_SquareScale, m_SquareRotation, m_SquareColor);
		DiloxGE::Renderer2D::EndScene();

		DiloxGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				DiloxGE::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		DiloxGE::Renderer2D::EndScene();
	}*/
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
		"Square Color",
		glm::value_ptr(player1.color),
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar
	);

	ImGui::DragFloat2("Translation", glm::value_ptr(player1.position), 0.1f);

	//ImGui::DragFloat("Rotation", &player1.rotation, 1.0f);

	//m_SquareRotation = m_SquareRotation >= 360.0f || m_SquareRotation <= -360.0f ? 0 : m_SquareRotation;

	ImGui::DragFloat2("Scale", glm::value_ptr(player1.scale), 0.1f);

	ImGui::DragFloat2("Translation2", glm::value_ptr(player2.position), 0.1f);

	//ImGui::DragFloat("Rotation2", &player2.rotation, 1.0f);

	//m_SquareRotation = m_SquareRotation >= 360.0f || m_SquareRotation <= -360.0f ? 0 : m_SquareRotation;

	ImGui::DragFloat2("Scale2", glm::value_ptr(player2.scale), 0.1f);

	ImGui::DragFloat("Animation Duration Time", &animSpeed, 0.1f);


	ImGui::End();
}

void Sandbox2D::OnEvent(DiloxGE::Event& e)
{
	m_CameraController.OnEvent(e);
}