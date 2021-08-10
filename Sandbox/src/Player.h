#pragma once 

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	Player(glm::vec3 pos, glm::vec2 size, float x, float y);
	//float animWalk[] = ;

	void MoveX()
	{
		m_Position.x += 0.5;
	}
};