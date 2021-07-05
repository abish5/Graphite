#include <Graphite.h>

#include "imgui/imgui.h"

class ExampleLayer : public Graphite::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		//if (Graphite::Input::IsKeyPressed(GP_KEY_TAB))
			//GP_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Graphite::Event& event) override
	{
		if (event.GetEventType() == Graphite::EventType::KeyPressed)
		{
			Graphite::KeyPressedEvent& e = (Graphite::KeyPressedEvent&)event;
			if (e.GetKeyCode() == GP_KEY_TAB)
				GP_TRACE("Tab key is pressed (event)!");
			GP_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Graphite::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};

Graphite::Application* Graphite::CreateApplication()
{
	return new Sandbox();
}