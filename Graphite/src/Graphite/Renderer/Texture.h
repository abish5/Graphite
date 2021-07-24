#pragma once

namespace Graphite {
	class Texture {
	public:
		Texture(const char* textPath);
		Texture();

		void Bind();
		void Unbind();

	private:
		uint32_t m_RendererID;

	};
}