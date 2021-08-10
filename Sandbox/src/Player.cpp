#include "gppch.h"

#include "Player.h"

Player::Player()
{}

Player::Player(glm::vec3 pos, glm::vec2 size, float x, float y)
	: GameObject(pos, size, x, y)
{
}