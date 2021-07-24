#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

namespace Graphite {

	class Renderer {
	public:
		static void BeginScene(Camera&);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform, const std::shared_ptr<Texture>& texture);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 viewProjMatrix = glm::mat4(1.0f);
		};

		 inline static SceneData* s_SceneData;
	};
}
