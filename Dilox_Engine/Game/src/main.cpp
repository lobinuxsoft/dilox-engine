#include <DiloxGE.h>

class ExampleLayer : public DiloxGE::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		DGE_INFO("ExampleLayer::Update");
	}

	void OnEvent(DiloxGE::Event& event) override
	{
		DGE_TRACE("{0}", event);
	}
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
