#include "gppch.h"

#include "SpriteRenderer.h"
#include "glad/glad.h"

namespace Graphite {

	SpriteRenderer::SpriteRenderer(std::shared_ptr<Shader> shader, glm::mat4 VPmatrix)
		: m_Shader(shader), m_CurrentVB(0), m_VPmatrix(VPmatrix)
	{
		initRenderData();
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::initRenderData()
	{
		m_VertexArray.reset(Graphite::VertexArray::Create());
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(nullptr, 1000 * 5 * sizeof(float)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float2, "a_TexCoord"},
		};
		vertexBuffer->SetLayout(layout);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		m_CurrentVB = vertexBuffer->GetID();
	}

	void SpriteRenderer::DrawSprite(std::shared_ptr<Graphite::Texture> texture, glm::vec3 position, glm::vec2 size, float m_SpriteCoordX, float m_SpriteCoordY, float rotate, glm::vec3 color)
	{
		m_Shader->Bind();

		float sheetWidth = 288.f, sheetHeight = 176.f;
		float spriteWidth = 16.f, spriteHeight = 16.f;

		float vertices[] = {
			0.0f, 0.0f, 0.0f, ((m_SpriteCoordX * spriteWidth) / sheetWidth), ((m_SpriteCoordY * spriteHeight) / sheetHeight),
			1.0f, 0.0f, 0.0f, (((m_SpriteCoordX + 1) * spriteWidth) / sheetWidth), ((m_SpriteCoordY * spriteHeight) / sheetHeight),
			1.0f, 1.0f, 0.0f, (((m_SpriteCoordX + 1) * spriteWidth) / sheetWidth), (((m_SpriteCoordY + 1) * spriteHeight) / sheetHeight),
			0.0f, 1.0f, 0.0f, ((m_SpriteCoordX * spriteWidth) / sheetWidth), (((m_SpriteCoordY + 1) * spriteHeight) / sheetHeight),
		};

		// Setting Dynamic Buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_CurrentVB);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(0, texture->getID());

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position));

		//model = glm::scale(model, glm::vec3(size, 1.0f));

		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat4("u_Model", model);
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat3("u_SpriteColor", color);
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat4("u_ViewProjection", m_VPmatrix);
		//std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat4("u_Transform", transform);


		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		m_VertexArray->Unbind();
	}
}