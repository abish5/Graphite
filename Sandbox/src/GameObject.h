#pragma once

#include "Graphite/Renderer/SpriteRenderer.h"
#include "Graphite/Renderer/Texture.h"
#include "glm/glm.hpp"

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec3 pos, glm::vec2 size, float x, float y, glm::vec2 velocity = glm::vec2(0.f, 0.f), glm::vec2 acc = glm::vec2(0.f, 0.f), glm::vec3 color = glm::vec3(1.f));
	glm::vec2 m_Size, m_Velocity, m_Acceleration;
	glm::vec3 m_Position, m_Color;
	float m_SpriteCoordX, m_SpriteCoordY;
	float m_Rotation;
	bool m_IsSolid;
	bool m_Destroyed;
	
	bool CheckCollision(GameObject obj);
	virtual void Draw(std::shared_ptr<Graphite::SpriteRenderer> renderer, std::shared_ptr<Graphite::Texture> texture);
};