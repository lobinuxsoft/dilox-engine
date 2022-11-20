#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) { }

void Sandbox2D::OnAttach()
{
	DGE_PROFILE_FUNCTION();

	//m_CheckerboardTexture = DiloxGE::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = DiloxGE::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	//m_TextureStairs = DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	//m_TextureBarrel = DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128, 128 });
	//m_TextureTree = DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 1 }, { 128, 128 }, { 1, 2 }));
	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 }));
	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 4, 1 }, { 128, 128 }, { 1, 2 }));
	anim.push_back(DiloxGE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 1 }, { 128, 128 }, { 1, 2 }));

	player1.m_SquarePos = { 0.0f,0.0f };
	player1.m_SquareScale = { 1.0f,1.0f };
	player1.m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };
	player1.m_SquareRotation = 0;

	player2.m_SquarePos = { 1.0f,1.0f };
	player2.m_SquareScale = { 1.0f,1.0f };
	player2.m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };
	player2.m_SquareRotation = 0;
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

	/*if (animTime > animDuration)
		animTime -= animDuration;*/


	DiloxGE::Renderer2D::DrawQuad(player1.m_SquarePos, player1.m_SquareScale, anim[static_cast<int>((animTime / animDuration) * anim.size()) % anim.size()]);

	DiloxGE::Renderer2D::DrawQuad(player2.m_SquarePos, player2.m_SquareScale, glm::vec4(1, 1, 1, 1));

	if (player1.m_SquarePos.x < player2.m_SquarePos.x + player2.m_SquareScale.x &&
		player1.m_SquarePos.x + player1.m_SquareScale.x > player2.m_SquarePos.x &&
		player1.m_SquarePos.y < player2.m_SquarePos.y + player2.m_SquareScale.y &&
		player1.m_SquarePos.y + player1.m_SquareScale.y > player2.m_SquarePos.y)
	{
		printf("Collision detected");
	}

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
		glm::value_ptr(player1.m_SquareColor),
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar
	);

	ImGui::DragFloat2("Translation", glm::value_ptr(player1.m_SquarePos), 0.1f);

	ImGui::DragFloat("Rotation", &player1.m_SquareRotation, 1.0f);

	//m_SquareRotation = m_SquareRotation >= 360.0f || m_SquareRotation <= -360.0f ? 0 : m_SquareRotation;

	ImGui::DragFloat2("Scale", glm::value_ptr(player1.m_SquareScale), 0.1f);

	ImGui::DragFloat2("Translation2", glm::value_ptr(player2.m_SquarePos), 0.1f);

	ImGui::DragFloat("Rotation2", &player2.m_SquareRotation, 1.0f);

	//m_SquareRotation = m_SquareRotation >= 360.0f || m_SquareRotation <= -360.0f ? 0 : m_SquareRotation;

	ImGui::DragFloat2("Scale2", glm::value_ptr(player2.m_SquareScale), 0.1f);

	ImGui::DragFloat("Animation Duration Time", &animSpeed, 0.1f);


	ImGui::End();
}

void Sandbox2D::OnEvent(DiloxGE::Event& e)
{
	m_CameraController.OnEvent(e);
}