#pragma once

#ifdef DGE_PLATFORM_WINDOWS

extern DiloxGE::BaseGame* DiloxGE::CreateBaseGame();

void main(int argc, char** argv)
{
	auto app = DiloxGE::CreateBaseGame();
	app->Run();
	delete app;
}

#endif // DGE_PLATFORM_WINDOWS