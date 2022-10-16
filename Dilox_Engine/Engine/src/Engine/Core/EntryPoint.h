/*
Basado en https://www.youtube.com/watch?v=meARMOmTLgE&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=5
*/

#pragma once
#include "Engine/Core/Core.h";

#ifdef DGE_PLATFORM_WINDOWS

extern DiloxGE::BaseGame* DiloxGE::CreateBaseGame();

void main(int argc, char** argv)
{
	DiloxGE::Log::Init();

	DGE_PROFILE_BEGIN_SESSION("Startup", "DiloxGEProfile-Startup.json");
	auto app = DiloxGE::CreateBaseGame();
	DGE_PROFILE_END_SESSION();

	DGE_PROFILE_BEGIN_SESSION("Runtime", "DiloxGEProfile-Runtime.json");
	app->Run();
	DGE_PROFILE_END_SESSION();

	DGE_PROFILE_BEGIN_SESSION("Startup", "DiloxGEProfile-Shutdown.json");
	delete app;
	DGE_PROFILE_END_SESSION();
}

#endif // DGE_PLATFORM_WINDOWS