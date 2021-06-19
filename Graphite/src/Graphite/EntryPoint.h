#pragma once

#ifdef GP_PLATFORM_WINDOWS

extern Graphite::Application* Graphite::CreateApplication();

int main(int argc, char** argv)
{
	Graphite::Log::Init();
	GP_CORE_WARN("Initialized Log!");
	int a = 5;
	GP_INFO("Hello! Var={0}", a);


	auto app = Graphite::CreateApplication();
	app->Run();
	delete app;
}

#endif