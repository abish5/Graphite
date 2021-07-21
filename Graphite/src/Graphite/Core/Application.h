#pragma once

#include "Core.h"
#include "Window.h"
#include "Graphite/Events/Event.h"
#include "Graphite/Events/ApplicationEvent.h"
#include "Graphite/Core/LayerStack.h"
#include "Graphite/Core/Timestep.h"
#include "Graphite/ImGui/ImGuiLayer.h"

namespace Graphite {
	class Application
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
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		inline static Application* s_Instance;
	};


	// To be defined in CLIENT
	Application* CreateApplication();
}
