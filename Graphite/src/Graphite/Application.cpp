#include "hzpch.h" 
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Graphite {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			GP_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			GP_TRACE(e);
		}

		while (true);
	}

}