#include <DiloxGE.h>

#include "imgui/imgui.h"

class ExampleLayer : public DiloxGE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
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

		std::shared_ptr<DiloxGE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(DiloxGE::VertexBuffer::Create(vertices, sizeof(vertices)));
		DiloxGE::BufferLayout layout = {
			{ DiloxGE::ShaderDataType::Float3, "a_Position"},
			{ DiloxGE::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<DiloxGE::IndexBuffer> indexBuffer;
		indexBuffer.reset(DiloxGE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(DiloxGE::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<DiloxGE::VertexBuffer> squareVB;
		squareVB.reset(DiloxGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ DiloxGE::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<DiloxGE::IndexBuffer> squareIB;
		squareIB.reset(DiloxGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new DiloxGE::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new DiloxGE::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(DiloxGE::Timestep ts) override
	{
		if (DiloxGE::Input::IsKeyPressed(DGE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if (DiloxGE::Input::IsKeyPressed(DGE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (DiloxGE::Input::IsKeyPressed(DGE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (DiloxGE::Input::IsKeyPressed(DGE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (DiloxGE::Input::IsKeyPressed(DGE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (DiloxGE::Input::IsKeyPressed(DGE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		DiloxGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DiloxGE::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		DiloxGE::Renderer::BeginScene(m_Camera);

		DiloxGE::Renderer::Submit(m_BlueShader, m_SquareVA);
		DiloxGE::Renderer::Submit(m_Shader, m_VertexArray);

		DiloxGE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(DiloxGE::Event& event) override
	{
		
	}

private:
	std::shared_ptr<DiloxGE::Shader> m_Shader;
	std::shared_ptr<DiloxGE::VertexArray> m_VertexArray;

	std::shared_ptr<DiloxGE::Shader> m_BlueShader;
	std::shared_ptr<DiloxGE::VertexArray> m_SquareVA;

	DiloxGE::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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
