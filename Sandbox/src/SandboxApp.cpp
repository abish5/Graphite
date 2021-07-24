#include <Graphite.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include "Graphite/Core/Input.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Graphite::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Graphite::VertexArray::Create());

		m_Texture.reset(new Graphite::Texture("src/Textures/wall.jpg"));

		float vertices[4 * 9] = {
			0.5f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.0f, 1.0f,
		};

		std::shared_ptr<Graphite::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Graphite::VertexBuffer::Create(vertices, sizeof(vertices)));
		Graphite::BufferLayout layout = {
			{ Graphite::ShaderDataType::Float3, "a_Position" },
			{ Graphite::ShaderDataType::Float4, "a_Color" },
			{ Graphite::ShaderDataType::Float2, "a_TexCoord"},
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<Graphite::IndexBuffer> indexBuffer;
		indexBuffer.reset(Graphite::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Squares
		m_SquareVA.reset(Graphite::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Graphite::VertexBuffer> squareVB;
		squareVB.reset(Graphite::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
				{ Graphite::ShaderDataType::Float3, "a_Position" }
			});
		
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Graphite::IndexBuffer> squareIB;
		squareIB.reset(Graphite::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		m_Shader.reset(Graphite::Shader::Create("src/Shaders/vertShader.glsl", "src/Shaders/fragShader.glsl"));

		m_FlatColorShader.reset(Graphite::Shader::Create("src/Shaders/flatVertShader.glsl", "src/Shaders/flatFragShader.glsl"));
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Graphite::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Graphite::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Graphite::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		
		Graphite::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f), m_Texture);

		Graphite::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Graphite::Event& event) override
	{

	}
private:
	std::shared_ptr<Graphite::Shader> m_Shader;
	std::shared_ptr<Graphite::VertexArray> m_VertexArray;
	std::shared_ptr<Graphite::Texture> m_Texture;

	std::shared_ptr<Graphite::Shader> m_FlatColorShader;
	std::shared_ptr<Graphite::VertexArray> m_SquareVA;

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