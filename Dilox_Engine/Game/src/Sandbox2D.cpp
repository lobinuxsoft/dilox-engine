#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) { }

void Sandbox2D::OnAttach() 
{
	DGE_PROFILE_FUNCTION();

	m_CheckerboardTexture = DiloxGE::Texture2D::Create("assets/textures/Checkerboard.png");
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
	{
		DGE_PROFILE_SCOPE("Renderer Prep");
		DiloxGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DiloxGE::RenderCommand::Clear();
	}

	{
		DGE_PROFILE_SCOPE("Renderer Draw");
		DiloxGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//DiloxGE::Renderer2D::DrawRotatedQuad(m_SquarePos, m_SquareScale, glm::radians(m_SquareRotation), m_SquareColor);
		//DiloxGE::Renderer2D::DrawRotatedQuad(m_SquarePos, m_SquareScale, glm::radians(m_SquareRotation), m_SquareColor);
		DiloxGE::Renderer2D::DrawQuad({ m_SquarePos }, { m_SquareScale }, { m_SquareColor });
		//DiloxGE::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		DiloxGE::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	DGE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	ImGui::ColorEdit4(
		"Square Color",
		glm::value_ptr(m_SquareColor),
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar
	);

	ImGui::DragFloat2("Translation", glm::value_ptr(m_SquarePos), 0.1f);

	ImGui::DragFloat("Rotation", &m_SquareRotation, 1.0f);

	m_SquareRotation = m_SquareRotation >= 360.0f || m_SquareRotation <= -360.0f ? 0 : m_SquareRotation;

	ImGui::DragFloat2("Scale", glm::value_ptr(m_SquareScale), 0.1f);

	ImGui::End();
}

void Sandbox2D::OnEvent(DiloxGE::Event& e)
{
	m_CameraController.OnEvent(e);
}