#pragma once
//#include <Graphite.h>

#include "Texture.h"
#include "Graphite/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glad/glad.h"

namespace Graphite {

	class SpriteRenderer
	{
	public:
		SpriteRenderer(glm::mat4 VPmatrix);
		~SpriteRenderer();
		
		template<typename T>
		void MultiDraw(std::vector<T> bgTiles, std::shared_ptr<Graphite::Texture> texture);

		void DrawSprite(int shaderPos, std::shared_ptr<Graphite::Texture> texture, glm::vec3 position, glm::vec2 size = glm::vec2(1.0f, 1.0f),
			float m_SpriteCoordX = 0.f, float m_SpriteCoordY = 0.f, float rotate = 0.0f,
			glm::vec3 color = glm::vec3(1.0f));

		void SetVPMatrix(glm::mat4 VP) { m_VPmatrix = VP; }
		void AddShader(std::shared_ptr<Shader>);

		void InitRenderData();
	private:
		std::vector<std::shared_ptr<Shader>> m_Shaders;
		std::vector<std::shared_ptr<VertexArray>> m_VertexArray;
		std::vector<uint32_t> m_CurrentVB;
		glm::mat4 m_VPmatrix;

	};

	template<typename T>
	void SpriteRenderer::MultiDraw(std::vector<T> bgTiles, std::shared_ptr<Graphite::Texture> texture)
	{
		m_Shaders.at(0)->Bind();				// HARD CODED TO SHADER 0
		std::vector<uint32_t> indices;
		std::vector<float> vertices;
		uint32_t firstIndex = 0; // start of the index of a quad
		float sheetWidth = 288.f, sheetHeight = 176.f;
		float spriteWidth = 16.f, spriteHeight = 16.f;


		for (int i = 0; i < bgTiles.size(); ++i)
		{
			float x = bgTiles.at(i).m_SpriteCoordX;
			float y = bgTiles.at(i).m_SpriteCoordY;

			//add current quads indices
			indices.insert(indices.end(), { firstIndex, firstIndex + 1, firstIndex + 2, firstIndex + 2, firstIndex + 3, firstIndex });
			firstIndex += 4;
			//add current quads vertex buffer info
			std::vector<float> v{ 0.0f + bgTiles[i].m_Position.x, 0.0f + bgTiles[i].m_Position.y, 0.0f, ((x * spriteWidth) / sheetWidth), ((y * spriteHeight) / sheetHeight),
				1.0f + bgTiles[i].m_Position.x, 0.0f + bgTiles[i].m_Position.y, 0.0f, (((x + 1) * spriteWidth) / sheetWidth), ((y * spriteHeight) / sheetHeight),
				1.0f + bgTiles[i].m_Position.x, 1.0f + bgTiles[i].m_Position.y, 0.0f, (((x + 1) * spriteWidth) / sheetWidth), (((y + 1) * spriteHeight) / sheetHeight),
				0.0f + bgTiles[i].m_Position.x, 1.0f + bgTiles[i].m_Position.y, 0.0f, ((x * spriteWidth) / sheetWidth), (((y + 1) * spriteHeight) / sheetHeight) };
			vertices.insert(vertices.end(), v.begin(), v.end());
		}

		//set new dynamic index buffer
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices.data(), indices.size()));

		m_VertexArray.at(0)->SetIndexBuffer(indexBuffer);

		// Setting Dynamic Buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_CurrentVB.at(0));
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
	
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();
		//GP_INFO("Texture: {0}", texture->getID());
		//set model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//send uniforms to shader
		std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.at(0))->UploadUniformMat4("u_Model", model);
		//std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.at(0))->UploadUniformFloat3("u_SpriteColor", bgTiles.at(i).m_Color);
		std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.at(0))->UploadUniformMat4("u_ViewProjection", m_VPmatrix);
		m_VertexArray.at(0)->Bind();
		glDrawElements(GL_TRIANGLES, m_VertexArray.at(0)->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		m_VertexArray.at(0)->Unbind();
		texture->Unbind();
	}

}