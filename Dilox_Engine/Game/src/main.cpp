#include <DiloxGE.h>

class Sandbox : public DiloxGE::BaseGame
{
	public:
		Sandbox() { }
		~Sandbox() { }
};

DiloxGE::BaseGame* DiloxGE::CreateBaseGame()
{
	return new Sandbox();
}

//void main()
//{
//	Sandbox* sandbox = new Sandbox();
//	sandbox->Run();
//	delete sandbox;
//}