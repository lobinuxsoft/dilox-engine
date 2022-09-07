#include <DiloxGE.h>

class ExampleLayer : public DiloxGE::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//DGE_INFO("ExampleLayer::Update");

		if (DiloxGE::Input::IsKeyPressed(DGE_KEY_TAB))
		{
			DGE_TRACE("Tab key is pressed!");
		}
	}

	void OnEvent(DiloxGE::Event& event) override
	{
		if (event.GetEventType() == DiloxGE::EventType::KeyPressed)
		{
			DiloxGE::KeyPressedEvent& e = (DiloxGE::KeyPressedEvent&)event;
			DGE_TRACE("{0}", (char)e.GetKeyCode()); //Si tocas la T, se muestra una T porque esta en ASCII
		}
	}
};

class Sandbox : public DiloxGE::BaseGame
{
	public:
		Sandbox() 
		{
			PushLayer(new ExampleLayer());
			PushOverlay(new DiloxGE::ImGuiLayer());
		}
		~Sandbox() { }
};

DiloxGE::BaseGame* DiloxGE::CreateBaseGame()
{
	return new Sandbox(); 
}
