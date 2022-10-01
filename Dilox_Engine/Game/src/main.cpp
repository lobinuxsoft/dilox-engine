#include <DiloxGE.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public DiloxGE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		// El proceso de dibujar un triangulo, el orden es importante de como se realizan las cosas
		// 1-Se crea el Vertex Array para poder conectar el Vertex Buffer
		// 2-Se setean los datos necesarios
		// 3-Se crea el Vertex Buffer
		// 4-S crea el Buffer Layout (sirve para poder conocer el Stride y el Offset de los datos)
		// 5-Se setea el Buffer Layout al Vertex Buffer
		// 6-Se agrega el Vertex Buffer al Vertex Array
		// 7-Se crea el Index Buffer y se lo conecta el Vertex Array
		// 8-Se crea el Shader

		m_VertexArray.reset(DiloxGE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		DiloxGE::Ref<DiloxGE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(DiloxGE::VertexBuffer::Create(vertices, sizeof(vertices)));
		DiloxGE::BufferLayout layout = {
			{ DiloxGE::ShaderDataType::Float3, "a_Position"},
			{ DiloxGE::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		DiloxGE::Ref<DiloxGE::IndexBuffer> indexBuffer;
		indexBuffer.reset(DiloxGE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(DiloxGE::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		DiloxGE::Ref<DiloxGE::VertexBuffer> squareVB;
		squareVB.reset(DiloxGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ DiloxGE::ShaderDataType::Float3, "a_Position" },
			{ DiloxGE::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		DiloxGE::Ref<DiloxGE::IndexBuffer> squareIB;
		squareIB.reset(DiloxGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = DiloxGE::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = DiloxGE::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = DiloxGE::Texture2D::Create("assets/textures/Checkerboard.png");
		m_CryingOnionTexture = DiloxGE::Texture2D::Create("assets/textures/CryingOnionLogo.png");

		std::dynamic_pointer_cast<DiloxGE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<DiloxGE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(DiloxGE::Timestep ts) override
	{
		//Update
		m_CameraController.OnUpdate(ts);
			
		//Render
		DiloxGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DiloxGE::RenderCommand::Clear();

		DiloxGE::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<DiloxGE::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<DiloxGE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (size_t y = 0; y < 20; y++)
		{
			for (size_t x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				DiloxGE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		DiloxGE::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_CryingOnionTexture->Bind();
		DiloxGE::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(2.5f, 1.0f, 0.0f)));

		// Triangle
		//DiloxGE::Renderer::Submit(m_Shader, m_VertexArray);

		DiloxGE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(DiloxGE::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	DiloxGE::ShaderLibrary m_ShaderLibrary;
	DiloxGE::Ref<DiloxGE::Shader> m_Shader;
	DiloxGE::Ref<DiloxGE::VertexArray> m_VertexArray;

	DiloxGE::Ref<DiloxGE::Shader> m_FlatColorShader;
	DiloxGE::Ref<DiloxGE::VertexArray> m_SquareVA;

	DiloxGE::Ref<DiloxGE::Texture2D> m_Texture, m_CryingOnionTexture; // CryingOnionLogo.png

	DiloxGE::OrtographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox : public DiloxGE::BaseGame
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() { }
};

DiloxGE::BaseGame* DiloxGE::CreateBaseGame()
{
	return new Sandbox();
}
