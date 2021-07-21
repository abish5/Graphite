#pragma once

#include <glm/glm.hpp>

#include "Graphite/Core/KeyCodes.h"
#include "Graphite/Core/MouseCodes.h"
namespace Graphite {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}