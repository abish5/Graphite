#include "gppch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Graphite {
	Shader* Shader::Create(const char* vertexPath, const char* fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    GP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexPath, fragmentPath);
		}
		GP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}