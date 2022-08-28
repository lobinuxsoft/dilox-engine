/*
Basado en https://www.youtube.com/watch?v=meARMOmTLgE&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=5
*/

#pragma once

#ifdef DGE_PLATFORM_WINDOWS

extern DiloxGE::BaseGame* DiloxGE::CreateBaseGame();

void main(int argc, char** argv)
{
	DiloxGE::Log::Init();
	DGE_CORE_WARN("Initialized Log!");

	auto app = DiloxGE::CreateBaseGame();
	app->Run();
	delete app;
}

#endif // DGE_PLATFORM_WINDOWS