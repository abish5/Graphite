#include <gppch.h>

#include "GameObject.h"

GameObject::GameObject()
	: m_Position(0.0f, 0.0f, 0.0f), m_Size(1.0f, 1.0f), m_Velocity(0.0f), m_Color(1.0f), 
	m_Rotation(0.0f), m_IsSolid(false), m_Destroyed(false), m_SpriteCoordX(0), m_SpriteCoordY(0)
{}

GameObject::GameObject(glm::vec3 pos, glm::vec2 size, float x, float y, glm::vec3 color, glm::vec2 velocity)
	: m_Position(pos), m_Size(size), m_Velocity(velocity), m_Color(color),
	m_Rotation(0.0f), m_IsSolid(false), m_Destroyed(false), m_SpriteCoordX(x), m_SpriteCoordY(y)
{}

void GameObject::Draw(std::shared_ptr<Graphite::SpriteRenderer> renderer, std::shared_ptr<Graphite::Texture> texture)
{
	renderer->DrawSprite(texture, m_Position, m_Size, m_SpriteCoordX, m_SpriteCoordY, m_Rotation, m_Color);
}