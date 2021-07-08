#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Graphite/Events/ApplicationEvent.h"
#include "Graphite/LayerStack.h"
#include "Graphite/ImGui/ImGuiLayer.h"

#include "Graphite/Renderer/Shader.h"
#include "Graphite/Renderer/Buffer.h"
#include "Graphite/Renderer/VertexArray.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		inline static Application* s_Instance;
	};


	// To be defined in CLIENT
	Application* CreateApplication();
}
