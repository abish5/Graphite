#include "gppch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphite {

	Camera::Camera(float l, float r, float b, float t)
		: m_projMatrix(glm::ortho(l, r, b, t, -1.0f, 1.0f)), m_viewMatrix(1.0f)
	{
		m_viewProjMatrix = m_projMatrix * m_viewMatrix;
	}
	Camera::~Camera()
	{
	}
	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_viewMatrix = glm::inverse(transform);
		m_viewProjMatrix = m_projMatrix * m_viewMatrix;
	}
}