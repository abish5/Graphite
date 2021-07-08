#include "gppch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Graphite {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
} 