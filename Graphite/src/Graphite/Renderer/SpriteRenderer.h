//#pragma once
//#include <Graphite.h>
//#include "Platform/OpenGL/OpenGLShader.h"
//
//namespace Graphite {
//	
//	class SpriteRenderer
//	{
//	public:
//		SpriteRenderer(Shader &shader);
//		~SpriteRenderer();
//
//		void DrawSprite(Texture2D& texture, glm::vec2 position,
//			glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
//			glm::vec3 color = glm::vec3(1.0f));
//	private:
//		std::shared_ptr<Shader> shader;
//		uint32_t quadVAO;
//
//		void initRenderData();
//	};
//}