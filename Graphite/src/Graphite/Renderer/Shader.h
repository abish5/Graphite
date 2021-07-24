#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Graphite {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t getID() const = 0;

		static Shader* Create(const char* vertexPath, const char* fragmentPath);
	};
}