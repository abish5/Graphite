#include "gppch.h"

#include "SpriteRenderer.h"
#include "glad/glad.h"

namespace Graphite {

	SpriteRenderer::SpriteRenderer(glm::mat4 VPmatrix)
		: m_CurrentVB(0), m_VPmatrix(VPmatrix)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::AddShader(std::shared_ptr<Shader> shader)
	{
		m_Shaders.push_back(shader);
	}
	void SpriteRenderer::InitRenderData()
	{
		std::shared_ptr<VertexArray> currVertArray;
		uint32_t VBO;

		currVertArray.reset(Graphite::VertexArray::Create());
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

		currVertArray->SetIndexBuffer(indexBuffer);
		currVertArray->AddVertexBuffer(vertexBuffer);
		
		VBO = vertexBuffer->GetID();

		m_VertexArray.push_back(currVertArray);
		m_CurrentVB.push_back(VBO);
	}

	void SpriteRenderer::DrawSprite(int shaderPos, std::shared_ptr<Graphite::Texture> texture, glm::vec3 position, glm::vec2 size, float m_SpriteCoordX, float m_SpriteCoordY, float rotate, glm::vec3 color)
	{
		m_Shaders.at(shaderPos)->Bind();

		float sheetWidth = 128.f, sheetHeight = 128.f;
		float spriteWidth = 11.f, spriteHeight = 12.f;

		float vertices[] = {
			0.0f, 0.0f, 0.0f, ((m_SpriteCoordX * spriteWidth) / sheetWidth), ((m_SpriteCoordY * spriteHeight) / sheetHeight),
			1.0f, 0.0f, 0.0f, (((m_SpriteCoordX + 1) * spriteWidth) / sheetWidth), ((m_SpriteCoordY * spriteHeight) / sheetHeight),
			1.0f, 1.0f, 0.0f, (((m_SpriteCoordX + 1) * spriteWidth) / sheetWidth), (((m_SpriteCoordY + 1) * spriteHeight) / sheetHeight),
			0.0f, 1.0f, 0.0f, ((m_SpriteCoordX * spriteWidth) / sheetWidth), (((m_SpriteCoordY + 1) * spriteHeight) / sheetHeight),
		};

		// Setting Dynamic Buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_CurrentVB.at(shaderPos));
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position));

		//model = glm::scale(model, glm::vec3(size, 5.0f));

		std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.at(shaderPos))->UploadUniformMat4("u_Model", model);
		std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.at(shaderPos))->UploadUniformFloat3("u_SpriteColor", color);
		std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.at(shaderPos))->UploadUniformMat4("u_ViewProjection", m_VPmatrix);


		m_VertexArray.at(shaderPos)->Bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, m_VertexArray.at(shaderPos)->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		m_VertexArray.at(shaderPos)->Unbind();
		texture->Unbind();
	}
}