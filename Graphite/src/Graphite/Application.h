#pragma once

#include "Core.h"
namespace Graphite {
	class GRAPHITE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}