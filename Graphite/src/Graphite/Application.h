#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Graphite/Events/ApplicationEvent.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Graphite/LayerStack.h"

namespace Graphite {
	class GRAPHITE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance;  }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	private:
		inline static Application* s_Instance;
	};


	// To be defined in CLIENT
	Application* CreateApplication();
}