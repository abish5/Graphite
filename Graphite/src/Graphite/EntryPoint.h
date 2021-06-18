#pragma once

#ifdef GP_PLATFORM_WINDOWS

extern Graphite::Application* Graphite::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Graphite::CreateApplication();
	app->Run();
	delete app;
}

#endif