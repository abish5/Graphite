#include <gppch.h>

#include "GameObject.h"

GameObject::GameObject()
	: m_Position(0.f, 0.f, 0.f), m_Size(1.f, 1.f), m_Velocity(0.f, 0.f), m_Acceleration(0.f, 0.f), m_Color(1.f), 
	m_Rotation(0.f), m_IsSolid(false), m_Destroyed(false), m_SpriteCoordX(0), m_SpriteCoordY(0)
{}

GameObject::GameObject(glm::vec3 pos, glm::vec2 size, float x, float y, glm::vec2 velocity, glm::vec2 acc, glm::vec3 color)
	: m_Position(pos), m_Size(size), m_Velocity(velocity), m_Acceleration(acc), m_Color(color),
	m_Rotation(0.f), m_IsSolid(false), m_Destroyed(false), m_SpriteCoordX(x), m_SpriteCoordY(y)  
{}

bool GameObject::CheckCollision(GameObject obj)
{
	//check bottom
	if (m_Position.y > obj.m_Position.y && m_Position.y < obj.m_Position.y + 1) {
		if (obj.m_Position.x < m_Position.x + m_Size.x && obj.m_Position.x > m_Position.x || m_Position.x < obj.m_Position.x + obj.m_Size.x && m_Position.x > obj.m_Position.x) {
			m_Velocity.y = 0;
			m_Acceleration.y = 0;
			return true;
		}
	}
	//check top
	else if (m_Position.y + 1 > obj.m_Position.y && m_Position.y < obj.m_Position.y) {
		if (obj.m_Position.x < m_Position.x + m_Size.x && obj.m_Position.x > m_Position.x || m_Position.x < obj.m_Position.x + obj.m_Size.x && m_Position.x > obj.m_Position.x) {
			//m_Acceleration += 9.8;
			m_Velocity.y = 0;
			m_Acceleration.y = 0;
			return true;
		}
	}
	//check left
	else if (m_Position.x > obj.m_Position.x && m_Position.x < obj.m_Position.x + 1) {
		if (obj.m_Position.y < m_Position.y + m_Size.y && obj.m_Position.y > m_Position.y || m_Position.y < obj.m_Position.y + obj.m_Size.y && m_Position.y > obj.m_Position.y) {
			m_Velocity.x = 0;
			m_Acceleration.x = 0;
			return true;
		}
	}
	//check right
	else if (m_Position.x + 1 > obj.m_Position.x && m_Position.x < obj.m_Position.x) {
		if (obj.m_Position.y < m_Position.y + m_Size.y && obj.m_Position.y > m_Position.y || m_Position.y < obj.m_Position.y + obj.m_Size.x && m_Position.y > obj.m_Position.y) {
			m_Velocity.x = 0;
			m_Acceleration.x = 0;			
			return true;
		}
	}

	return false;
}

void GameObject::Draw(std::shared_ptr<Graphite::SpriteRenderer> renderer, std::shared_ptr<Graphite::Texture> texture)
{
	renderer->DrawSprite(0, texture, m_Position, m_Size, m_SpriteCoordX, m_SpriteCoordY, m_Rotation, m_Color);
}