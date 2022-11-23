#include <DiloxGE.h>
#include <Engine/Core/EntryPoint.h>

#include "Sandbox2D.h"

#include "ExampleLayer.h"

class Sandbox : public DiloxGE::BaseGame
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() { }
};

DiloxGE::BaseGame* DiloxGE::CreateBaseGame()
{
	return new Sandbox();
}
