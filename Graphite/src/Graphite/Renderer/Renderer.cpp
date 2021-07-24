#include "gppch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "glad/glad.h"
namespace Graphite {

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData = new SceneData;
		s_SceneData->viewProjMatrix = camera.GetViewProjMatrix();
	}
	
	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->viewProjMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform, const std::shared_ptr<Texture>& texture)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->viewProjMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		glUniform1i(glGetUniformLocation(shader->getID(), "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
