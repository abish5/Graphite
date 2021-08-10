#include <Graphite.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include "Graphite/Core/Input.h"
#include "Player.h"

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
		m_Shader2.reset(Graphite::Shader::Create("src/Shaders/charVert.glsl", "src/Shaders/charFrag.glsl"));
		m_CharSheet.reset(new Graphite::Texture("src/Tileset/oubliette_tileset_t.png"));
		m_Tileset.reset(new Graphite::Texture("src/Tileset/tileset.png"));
		std::dynamic_pointer_cast<Graphite::OpenGLShader>(m_Shader)->UploadUniformInt("image", 0);
		std::dynamic_pointer_cast<Graphite::OpenGLShader>(m_Shader2)->UploadUniformInt("image", 0);
		m_Level.reset(new GameLevel(m_Tileset));
		m_Level->Load("src/Levels/level1.txt", 640, 360);
		m_Renderer.reset(new Graphite::SpriteRenderer(m_Camera.GetViewProjMatrix()));
		m_Renderer->AddShader(m_Shader);
		m_Renderer->InitRenderData();
		m_Renderer->AddShader(m_Shader2);
		m_Renderer->InitRenderData();
		m_Player.reset(new Player(glm::vec3(1.0f, 2.0f, 0.0f), glm::vec2(0.6, 1.0909091), 0, 0));
	}

	void OnUpdate(Graphite::Timestep ts) override
	{
		bool isAccelerating = false;
		if (Graphite::Input::IsKeyPressed(65)){
			isAccelerating = true;
			//m_CameraPosition.x -= m_CameraMoveSpeed * ts;
			if (m_Player->m_Acceleration.x - 5.f < -10.f) {
				m_Player->m_Acceleration.x = -10.f;
			}
			else {
				m_Player->m_Acceleration.x -= 5.f;
			}
		}
		if (Graphite::Input::IsKeyPressed(68)) {
			isAccelerating = true;
			//m_CameraPosition.x += m_CameraMoveSpeed * ts;
			if (m_Player->m_Acceleration.x + 5.f > 10.f) {
				m_Player->m_Acceleration.x = 10.f;
			}
			else {
				m_Player->m_Acceleration.x += 5.f;
			}
		}
		if (Graphite::Input::IsKeyPressed(87)) {				//ONLY ACTIVE FOR COLLISION TESTING
			//m_CameraPosition.y += m_CameraMoveSpeed * ts;
			//if (m_Player->m_Acceleration.y + 4.f >= 10.f) {
			//	m_Player->m_Acceleration.y = 10.f;
			//}
			//else {
			//	m_Player->m_Acceleration.y += 4.f;
			//}
			m_Player->m_Position.y += 0.25;
		}

		//GP_INFO("Y ACCELERATION: {0}", m_Player->m_Acceleration.y);
		//GP_INFO("X VELOCITY: {0}", m_Player->m_Velocity.x);
		// Apply forces
		// x direction
		// check if accelerating

		//calculate current velocity
		glm::vec2 v2 = { 0.0f, 0.0f };
 
		v2.x = m_Player->m_Velocity.x + m_Player->m_Acceleration.x * ts;
		if (isAccelerating == false) {
			m_Player->m_Acceleration.x -= m_Player->m_Acceleration.x;
			if (v2.x < 0.01f && v2.x > -0.01f)
				v2.x = 0;
			else
				v2.x *= 0.9;
		}
		m_Player->m_Position.x += 0.5 * (v2.x + m_Player->m_Velocity.x) * ts;

		// y direction
		// check if accelerating
		// apply gravity
		m_Player->m_Acceleration.y -= 0.9;
		//calculate current velocity
		v2.y = m_Player->m_Velocity.y + m_Player->m_Acceleration.y * ts;
		m_Player->m_Position.y += 0.5 * (v2.y + m_Player->m_Velocity.y) * ts;

		m_Player->m_Velocity = v2;
		
		//Check Collisions
		for (int i = 0; i < m_Level->m_BGTiles.size(); ++i) {
			m_Player->CheckCollision(m_Level->m_BGTiles.at(i));
		}

		Graphite::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Graphite::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Graphite::Renderer::BeginScene(m_Camera);

		m_Renderer->SetVPMatrix(m_Camera.GetViewProjMatrix());
		m_Level->DrawBackground(m_Renderer);
		float xCoordAnim = 0.27272727f;

		m_Renderer->DrawSprite(1, m_CharSheet, m_Player->m_Position, glm::vec2(1.0f, 1.0f), 0.27272727f, 0.f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));

		//Graphite::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));

		Graphite::Renderer::EndScene();
	}

	virtual void OnImGuiRender(Graphite::Timestep ts) override
	{
		ImGui::Begin("Info");
		ImGui::Text("framerate: %f", 1 / ts.GetSeconds());
		ImGui::Text("X Acceleration: %.2f", m_Player->m_Acceleration.x);
		ImGui::Text("Y Acceleration: %.2f", m_Player->m_Acceleration.y);
		ImGui::Text("X m_Position: %.2f", m_Player->m_Position.x);
		ImGui::Text("Y m_Position: %.2f", m_Player->m_Position.y);

		ImGui::End();
	}

	void OnEvent(Graphite::Event& event) override
	{
	}
private:
	std::shared_ptr<Graphite::Shader> m_Shader;
	std::shared_ptr<Graphite::Shader> m_Shader2;
	std::shared_ptr<Graphite::SpriteRenderer> m_Renderer;
	std::shared_ptr<Graphite::Texture> m_Tileset;
	std::shared_ptr<Graphite::Texture> m_CharSheet;
	std::shared_ptr<GameLevel> m_Level;
	std::shared_ptr<Player> m_Player;

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