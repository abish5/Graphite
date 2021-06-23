#include <Graphite.h>

class ExampleLayer : public Graphite::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		GP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Graphite::Event& event) override
	{
		GP_TRACE("{0}", event);
	}
};

class Sandbox : public Graphite::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Graphite::ImGuiLayer());
	}
	~Sandbox() {

	}
};

Graphite::Application* Graphite::CreateApplication()
{
	return new Sandbox();
}