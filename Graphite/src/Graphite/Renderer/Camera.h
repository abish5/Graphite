#pragma once

#include "glm/glm.hpp"

namespace Graphite {
	class Camera {
	public:
		Camera(float left, float right, float bottom, float top);
		~Camera();
		
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix();  }

		const glm::mat4& GetProjMatrix() const { return m_projMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetViewProjMatrix() const { return m_viewProjMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }
		float getRotation() { return m_Rotation; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_projMatrix = glm::mat4(1.0f);
		glm::mat4 m_viewMatrix = glm::mat4(1.0f);
		glm::mat4 m_viewProjMatrix = glm::mat4(1.0f);

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}