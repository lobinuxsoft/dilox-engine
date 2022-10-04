#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) { }

void Sandbox2D::OnAttach() 
{
	m_CheckerboardTexture = DiloxGE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(DiloxGE::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	DiloxGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	DiloxGE::RenderCommand::Clear();

	DiloxGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
	DiloxGE::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	DiloxGE::Renderer2D::DrawQuad(m_SquarePos, m_SquareScale, m_SquareColor);
	DiloxGE::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	DiloxGE::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4(
		"Square Color",
		glm::value_ptr(m_SquareColor),
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar
	);

	ImGui::DragFloat2("Position", glm::value_ptr(m_SquarePos), 0.1f);
	ImGui::DragFloat2("Scale", glm::value_ptr(m_SquareScale), 0.1f);

	ImGui::End();
}

void Sandbox2D::OnEvent(DiloxGE::Event& e)
{
	m_CameraController.OnEvent(e);
}