#include <Graphite.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include "Graphite/Core/Input.h"

#include "GameLevel.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ASPECT_RATIO 1.77777777778

class ExampleLayer : public Graphite::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(0.f, ASPECT_RATIO * 11.f, 0.f, 11.f), m_CameraPosition(0.0f)
	{
		m_Shader.reset(Graphite::Shader::Create("src/Shaders/spriteVert.glsl","src/Shaders/spriteFrag.glsl"));
		m_Texture.reset(new Graphite::Texture("src/Tileset/tileset.png"));
		std::dynamic_pointer_cast<Graphite::OpenGLShader>(m_Shader)->UploadUniformInt("image", 0);
		m_Level.reset(new GameLevel(m_Texture));
		m_Level->Load("src/Levels/level1.txt", 640, 360);
		m_Renderer.reset(new Graphite::SpriteRenderer(m_Shader, m_Camera.GetViewProjMatrix()));
	}

	void OnUpdate(Graphite::Timestep ts) override
	{
		if (Graphite::Input::IsKeyPressed(65))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Graphite::Input::IsKeyPressed(68))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Graphite::Input::IsKeyPressed(87))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Graphite::Input::IsKeyPressed(83))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Graphite::Input::IsKeyPressed(74))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Graphite::Input::IsKeyPressed(75))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Graphite::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Graphite::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Graphite::Renderer::BeginScene(m_Camera);

		m_Renderer->SetVPMatrix(m_Camera.GetViewProjMatrix());
		//m_Level->Draw(m_Renderer);
		m_Level->DrawBackground(m_Renderer);
		//m_Renderer->DrawSprite(m_Texture, glm::vec3(0.0f, 0.0f, 0.0f), m_Camera.GetViewProjMatrix(), glm::mat4(1.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));

		//Graphite::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));

		Graphite::Renderer::EndScene();
	}

	virtual void OnImGuiRender(Graphite::Timestep ts) override
	{
		ImGui::Begin("Info");
		ImGui::Text("framerate: %f", 1 / ts.GetSeconds());
		ImGui::End();
	}

	void OnEvent(Graphite::Event& event) override
	{
	}
private:
	std::shared_ptr<Graphite::Shader> m_Shader;
	std::shared_ptr<Graphite::SpriteRenderer> m_Renderer;
	std::shared_ptr<Graphite::Texture> m_Texture;
	std::shared_ptr<GameLevel> m_Level;

	Graphite::Camera m_Camera; 
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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